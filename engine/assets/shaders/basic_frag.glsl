#version 330 core
//A frag shader requires there to be a single out of a vec4 to define the final colour of said pixel/fragment
out vec4 FragColour;

void main() {
    FragColour = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}