attribute vec4 Position;
uniform mat4 Modelview;
attribute vec2 TexCoordIn;
varying vec2 TexCoordOut;

void main(void) {
    gl_Position = Modelview * Position;
    TexCoordOut = TexCoordIn;
}