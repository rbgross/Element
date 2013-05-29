#version 150
out vec4 outColor;
out uvec3 pickingData;
uniform uint objectID;
void main() {
	pickingData = uvec3( objectID, objectID, objectID );
}