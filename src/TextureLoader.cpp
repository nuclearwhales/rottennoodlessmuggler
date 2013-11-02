#include "TextureLoader.h"

#include <Containers/Array.h>
#include <Utility/Resource.h>
#include <Trade/ImageData.h>
#include <Texture.h>
#include <TextureFormat.h>

namespace Rotten {

TextureLoader::TextureLoader() {
    tgaImporter = Manager::instance().get<Trade::AbstractImporter>("tga-importer");

    Utility::Resource rs("textures");

    /* Remove `.tga` extensions from the names */
    for(const auto& filename: rs.list()) {
        auto name = filename.substr(0, filename.size()-4);
        names.emplace(name, name);
    }
}

void TextureLoader::doLoad(ResourceKey key) {
    auto found = names.find(key);
    if(found == names.end()) return setNotFound(key);

    Utility::Resource rs("textures");
    if(!tgaImporter->openData(rs.getRaw(found->second + ".tga"))) {
        Error() << "TextureLoader: cannot open" << found->second;
        return setNotFound(key);
    }

    auto image = tgaImporter->image2D(0);
    if(!image) {
        Error() << "TextureLoader: cannot load" << found->second;
        return setNotFound(key);
    }

    auto texture = new Texture2D;
    texture->setMinificationFilter(Sampler::Filter::Nearest)
        .setMagnificationFilter(Sampler::Filter::Nearest)
        .setWrapping(Sampler::Wrapping::ClampToEdge);

    #ifndef MAGNUM_TARGET_GLES
    texture->setImage(0, TextureFormat::RGB, *image);
    #else
    texture->setImage(0, TextureFormat::Luminance, *image);
    #endif

    set(key, texture);
}

std::string TextureLoader::doName(ResourceKey key) const {
    auto found = names.find(key);
    return found == names.end() ? "" : found->second;
}

}
