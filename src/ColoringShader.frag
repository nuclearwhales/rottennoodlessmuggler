uniform sampler2D lookupTexture;
uniform sampler2D inputTexture;

varying mediump vec2 interpolatedTextureCoordinates;

void main() {
    gl_FragColor = texture2D(lookupTexture, vec2(texture2D(inputTexture, interpolatedTextureCoordinates).x, 0));
}
