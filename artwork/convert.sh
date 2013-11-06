for i in bag box button{-a,-b,-selected} dumpster-o{ff,n} mess strongbox ; do
    convert ${i}.png -type grayscale ../data/${i}.tga
done
