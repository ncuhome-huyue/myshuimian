#version 450 core

in vec3 fc;

out vec4 color;

void main(){
//    vec3 c=mix(texture(texture1,fs_in.TexCoords),texture(texture2,fs_in.TexCoords),0.2).rgb;
//    vec3 lightDir=normalize(lightPos-fs_in.FragPos);
//    vec3 viewDir=normalize(viewPos-fs_in.FragPos);
//    vec3 halfDir=normalize(lightDir+viewDir);
//    float spec = pow(max(dot(fs_in.Normal, halfDir), 0.0), 256.0);
//    float diff = max(dot(lightDir,fs_in.Normal),0.0);
//    vec3 ambient = c*lightColor*0.05;
//    vec3 diffuse = c*diff;
//    vec3 specular = lightColor*spec*0.3;
//    color=vec4(ambient + diffuse + specular, 1.0);;
    color=vec4(1,1,1,1.0);
}