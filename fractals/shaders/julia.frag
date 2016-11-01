#version 300 es

precision highp float;

in highp vec2 aCoords;
out highp vec4 color;

void main()
{
    float zRe = aCoords.x;
    float zIm = aCoords.y;
    float nextRe;
    float nextIm;
    float squareModule;

    int i;
    int iterations = 300;
    for (i = 0; i < iterations; ++i)
    {
        nextRe = zRe*zRe - zIm*zIm - 0.1;
        nextIm = 2.0*zRe*zIm + 0.65;

        squareModule = nextRe*nextRe + nextIm*nextIm;
        if (squareModule > 4.0f)
        {
            break;
        }

        zRe = nextRe;
        zIm = nextIm;
    }

    float c = float(i) / float(iterations);
    color = vec4(c, c, c, 1.0);
}
