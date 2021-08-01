#ifndef TEXTURE_H
#define TEXTURE_H
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Logger.h"
#include <stb_image/stb_image.h>
#include <string>
#include <vector>

struct TextureManager{
public:
    Logger* logger;
    std::vector<unsigned int> ListOfTextureId;
    std::vector<std::string> ListOfTextureNames;
    std::vector<std::string> ListOfTextureSpec;
    std::vector<unsigned int> ListOfActivatedTexture;

    //Constructor
    TextureManager(Logger* logger){
        this->logger = logger;
    }

    //Adds Texture object to list
    void AddTexture(std::string filename="default.jpg"){
        ListOfTextureId.push_back(-1);
            //Loads texture file
            const char* file = filename.c_str();
            int width, height, nrChannels;
            this->logger = logger;
            unsigned char* data = stbi_load(file, &width, &height, &nrChannels, STBI_rgb);
            logger->Log("Image Loaded");

            //Generates Texutre OpenGL Object
            glGenTextures(1, &ListOfTextureId.back());
            logger->Log("Generated Texture ID");
            glBindTexture(GL_TEXTURE_2D, ListOfTextureId.back());
            logger->Log("Binded Texture ID");
            if (data) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
                logger->Log("Generated Mipmap");
            }
            else {
                logger->Log("Failed to load texture", true);
                throw "Failed to load texture";
            }
            stbi_image_free(data);
            this->logger->Log("Removed Image Data");
            ListOfTextureNames.push_back(filename);
    }

    //Draws texture name
    void Draw(std::string filename){
        for(int i=0; i < ListOfTextureNames.size(); i++){
            if(ListOfTextureNames[i] == filename){
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, ListOfTextureId[i]);
            }
        }
    }

    //Gets TextureID
    int GetTextureId(std::string filename){
        for(int i=0; i < ListOfTextureNames.size(); i++){
            if(ListOfTextureNames[i] == filename){
                    return ListOfTextureId[i];
            }
        }
        return -1;
    }

    //Destructor
    ~TextureManager() {
        for(int i=0; i < ListOfTextureNames.size(); i++){
            glActiveTexture(GL_TEXTURE0 + ListOfTextureId[i]);
            glDeleteTextures(1, &ListOfTextureId[i]);
            logger->Log("Removed Texture Data (FROM CLEARGPUMEMORY)");
        }
	}
};

#endif
