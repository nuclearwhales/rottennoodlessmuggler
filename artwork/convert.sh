for i in box dumpster-off dumpster-on mess strongbox ; do
    convert ${i}.png -type grayscale ../data/${i}.tga
done
