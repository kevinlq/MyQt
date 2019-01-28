uniform vec4 baseColor;

uniform float rangeStart;
uniform float rangeEnd;

varying vec4 vertex;

void main(void)
{
    float level;
    level = -vertex.z;

    if (level < rangeStart || level > rangeEnd) {
        discard;
    }

    gl_FragColor = baseColor;
}
