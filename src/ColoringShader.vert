attribute highp vec2 position;

attribute mediump vec2 textureCoordinates;
varying mediump vec2 interpolatedTextureCoordinates;

void main() {
    gl_Position = vec4(position, 0.0, 1.0);
    interpolatedTextureCoordinates = textureCoordinates;
}
