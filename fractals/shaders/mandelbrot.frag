#version 300 es

precision highp float;

in highp vec2 vCoords;
out highp vec4 color;

void main()
{
    float zRe = 0.0;
    float zIm = 0.0;
    float nextRe;
    float nextIm;
    float squareModule;

    int i;
    for (i = 0; i < 100; ++i)
    {
        nextRe = zRe*zRe - zIm*zIm + vCoords.x;
        nextIm = 2.0*zRe*zIm + vCoords.y;

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
