attribute vec4 qt_Vertex;
uniform mat4 qt_ModelViewProjectionMatrix;
varying vec4 vertexPosition;

void main(void)
{
    vertexPosition = qt_ModelViewProjectionMatrix * qt_Vertex;
    gl_Position = vertexPosition;
}
