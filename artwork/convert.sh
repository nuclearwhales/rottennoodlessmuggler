for i in box mess strongbox ; do
    convert ${i}.png -type grayscale ../data/${i}.tga
done
