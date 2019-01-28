uniform float antennaPosition;
uniform vec4 baseColor;
varying vec4 vertexPosition;
uniform float elevStart;
uniform float elevEnd;

void main(void)
{
    float angle;
    float diff;
    float elev;
    vec4 pos;
    vec4 color;
    pos = vertexPosition;
    elev = -vertexPosition.z * 90.0;
    if (elev < elevStart || elev > elevEnd) {
        discard;
    }
    if (pos.x > 0.0) {
        if (pos.y > 0.0)
            angle = degrees(atan(pos.x/pos.y));
        else
            angle = 180.0 - degrees(atan(-pos.x/pos.y));
    } else {
        if (pos.y > 0.0)
            angle = 360.0 - degrees(atan(-pos.x/pos.y));
        else
            angle = 180.0 + degrees(atan(pos.x/pos.y));
    }
    if (angle <= antennaPosition)
        diff = antennaPosition-angle;
    else
        diff = 360.0-(angle-antennaPosition);
    gl_FragColor = mix(baseColor, vec4(0.0,0.0,0.0,0.0), diff/360.0);
}
