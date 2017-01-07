#version 300 es

precision highp float;

in highp vec2 aCoords;
out highp vec4 color;

uniform vec2 inZ0;

void main()
{
    float zRe = inZ0.x;
    float zIm = inZ0.y;
    float nextRe;
    float nextIm;
    float squareModule;

    int i;
    for (i = 0; i < 100; ++i)
    {
        nextRe = zRe*zRe - zIm*zIm + aCoords.x;
        nextIm = 2.0*zRe*zIm + aCoords.y;

        squareModule = nextRe*nextRe + nextIm*nextIm;
        if (squareModule > 4.0f)
        {
            break;
        }

        zRe = nextRe;
        zIm = nextIm;
    }

    float c = float(i) / 100.0;
    color = vec4(c, c, c, 1.0);
}
