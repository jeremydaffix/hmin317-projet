#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;

attribute vec4 a_position;

varying vec2 v_texcoord;

varying vec3 terrain_color;


//! [0]
void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * a_position;


    if (a_position.z > 1.9) // neige
    {
       terrain_color = vec3(1.0, 1.0, 1.0);
    }

    else if (a_position.z > 1.0) // montagne haut, cailloux + herbe
    {
       terrain_color = vec3(0.3, 0.7, 0.3);
    }

    else if (a_position.z < 0.60) // eau
    {
       terrain_color = vec3(0.2, 0.2, 0.85);
    }

    else // montagne bas, végétation
    {
        terrain_color = vec3(0.2, 0.65, 0.2);
    }
}
//! [0]
