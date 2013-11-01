#ifndef Rotten_ResourceLoader_h
#define Rotten_ResourceLoader_h

#include <unordered_map>
#include <AbstractResourceLoader.h>
#include <Resource.h>
#include <Trade/AbstractImporter.h>

#include "Rotten.h"

namespace Rotten {

class TextureLoader: public AbstractResourceLoader<Texture2D> {
    public:
        explicit TextureLoader();

        void doLoad(ResourceKey key) override;
        std::string doName(ResourceKey key) const override;

    private:
        std::unordered_map<ResourceKey, std::string> names;

        Resource<Trade::AbstractImporter> tgaImporter;
};

}

#endif
