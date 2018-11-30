#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;

varying vec3 terrain_color;


//! [0]
void main()
{
    gl_FragColor = vec4(terrain_color, 1.0);

}
//! [0]

