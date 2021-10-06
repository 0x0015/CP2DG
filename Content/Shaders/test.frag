varying vec4 color;
varying vec2 texCoord;

uniform vec2 resolution;
uniform float globalTime;

void main() {
    vec2 uv = gl_FragCoord.xy/resolution.xy;

    // Time varying pixel color
    vec3 col = 0.5 + 0.5*cos(globalTime+uv.xyx+vec3(0,2,4));

    // Output to screen
    gl_FragColor = vec4(col,1.0);
	//gl_FragColor = vec4(1.0,0.0,0.0, 1.0);
}	
