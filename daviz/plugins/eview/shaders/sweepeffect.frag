uniform sampler2D qt_Texture0;
varying vec4 qt_TexCoord0;

uniform float antennaPosition;
uniform vec4 baseColor;
uniform float rangeStart;
uniform float rangeEnd;

void main(void)
{

    float angle;
    float diff;

    angle = qt_TexCoord0.s * 360.0;
    if (angle <= antennaPosition)
        diff = antennaPosition-angle;
    else
        diff = 360.0-(angle-antennaPosition);

    vec4 color = texture2D(qt_Texture0, qt_TexCoord0.st);
    gl_FragColor = mix(color, vec4(0., 0., 0., 0.), diff/360.0);
}
