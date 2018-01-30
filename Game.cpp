#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <glm/gtx/euler_angles.hpp>//rotation
#include <glm/gtx/norm.hpp>//rotation
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>


int main( void )
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);


    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);

    // Open a window and create its OpenGL context
    //glfwOpenWindow( int width, int height, int redbits,int greenbits, int bluebits, int alphabits, int depthbits,int stencilbits, int mode )
    //redbits,greenbits,bluebits: number of bits to use for each color.(0 means default color depth)
    //mode: specifies whether we will open a GLFW_FullScreen or a GLFW_WINDOW
    if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )
    {
        fprintf( stderr, "Failed to open GLFW window.\n" );
        glfwTerminate();
        return -1;
    }

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    glfwSetWindowTitle( "Food Invaders" );

    // Ensure we can capture the escape key being pressed below
    glfwEnable( GLFW_STICKY_KEYS );


    // Dark purple background
    glClearColor(0.4f, 0.0f, 0.4f, 0.0f);


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );

    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
    GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

    // Get a handle for our buffers
    GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
    GLuint vertexUVID = glGetAttribLocation(programID, "vertexUV");
    GLuint vertexNormal_modelspaceID = glGetAttribLocation(programID, "vertexNormal_modelspace");

    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    glm::mat4 View       = glm::lookAt(
                                glm::vec3(0,0,-10), //position
                                glm::vec3(0,0,0), // and looks at the origin
                                glm::vec3(0,1,0)  // Head is up
                           );

    // Load the texture
    GLuint Texture = loadBMP_custom("skin.bmp");
    GLuint Texture1 = loadBMP_custom("BoxText.bmp");
    GLuint Texture2 = loadBMP_custom("coca-cola-zero.bmp");
    GLuint Texture3 = loadBMP_custom("spongebob.bmp");
    GLuint Texture4 = loadBMP_custom("1162335_1357056071789_full11.bmp");

    // Get a handle for our "myTextureSampler" uniform
    GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
//*********************************************************************************************************************[APPLE]
    // Read first model -apple-
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals; // Won't be used at the moment.
    bool res = loadOBJ("apple.obj", vertices, uvs, normals);


    // Load it into a VBO

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    GLuint normalbuffer;
    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);




//********************************************************************************************************************[BOX]
    // Read second model -Box-
    std::vector<glm::vec3> vertices1;
    std::vector<glm::vec2> uvs1;
    std::vector<glm::vec3> normals1; // Won't be used at the moment.
    bool res1 = loadOBJ("Box.obj", vertices1, uvs1, normals1);


    // Load it into a VBO

    GLuint vertexbuffer1;
    glGenBuffers(1, &vertexbuffer1);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
    glBufferData(GL_ARRAY_BUFFER, vertices1.size() * sizeof(glm::vec3), &vertices1[0], GL_STATIC_DRAW);

    GLuint uvbuffer1;
    glGenBuffers(1, &uvbuffer1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer1);
    glBufferData(GL_ARRAY_BUFFER, uvs1.size() * sizeof(glm::vec2), &uvs1[0], GL_STATIC_DRAW);

    GLuint normalbuffer1;
    glGenBuffers(1, &normalbuffer1);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer1);
    glBufferData(GL_ARRAY_BUFFER, normals1.size() * sizeof(glm::vec3), &normals1[0], GL_STATIC_DRAW);

//********************************************************************************************************************[COCACOLA]
    std::vector<glm::vec3> vertices2;
    std::vector<glm::vec2> uvs2;
    std::vector<glm::vec3> normals2; // Won't be used at the moment.
    bool res2 = loadOBJ("cocacola.obj", vertices2, uvs2, normals2);


    // Load it into a VBO

    GLuint vertexbuffer2;
    glGenBuffers(1, &vertexbuffer2);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
    glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(glm::vec3), &vertices2[0], GL_STATIC_DRAW);

    GLuint uvbuffer2;
    glGenBuffers(1, &uvbuffer2);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer2);
    glBufferData(GL_ARRAY_BUFFER, uvs2.size() * sizeof(glm::vec2), &uvs2[0], GL_STATIC_DRAW);

    GLuint normalbuffer2;
    glGenBuffers(1, &normalbuffer2);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer2);
    glBufferData(GL_ARRAY_BUFFER, normals2.size() * sizeof(glm::vec3), &normals2[0], GL_STATIC_DRAW);
//*****************************************************************************************************************[character]
    std::vector<glm::vec3> vertices3;
    std::vector<glm::vec2> uvs3;
    std::vector<glm::vec3> normals3; // Won't be used at the moment.
    bool res3 = loadOBJ("SpongeBob.obj", vertices3, uvs3, normals3);


    // Load it into a VBO

    GLuint vertexbuffer3;
    glGenBuffers(1, &vertexbuffer3);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer3);
    glBufferData(GL_ARRAY_BUFFER, vertices3.size() * sizeof(glm::vec3), &vertices3[0], GL_STATIC_DRAW);

    GLuint uvbuffer3;
    glGenBuffers(1, &uvbuffer3);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer3);
    glBufferData(GL_ARRAY_BUFFER, uvs3.size() * sizeof(glm::vec2), &uvs3[0], GL_STATIC_DRAW);

    GLuint normalbuffer3;
    glGenBuffers(1, &normalbuffer3);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer3);
    glBufferData(GL_ARRAY_BUFFER, normals3.size() * sizeof(glm::vec3), &normals3[0], GL_STATIC_DRAW);
//*****************************************************************************************************************[KIWI]
    /*std::vector<glm::vec3> vertices4;
    std::vector<glm::vec2> uvs4;
    std::vector<glm::vec3> normals4; // Won't be used at the moment.
    bool res4 = loadOBJ("Kiwi.obj", vertices4, uvs4, normals4);


    // Load it into a VBO

    GLuint vertexbuffer4;
    glGenBuffers(1, &vertexbuffer4);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer4);
    glBufferData(GL_ARRAY_BUFFER, vertices4.size() * sizeof(glm::vec3), &vertices4[0], GL_STATIC_DRAW);

    GLuint uvbuffer4;
    glGenBuffers(1, &uvbuffer4);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer4);
    glBufferData(GL_ARRAY_BUFFER, uvs4.size() * sizeof(glm::vec2), &uvs4[0], GL_STATIC_DRAW);

    GLuint normalbuffer4;
    glGenBuffers(1, &normalbuffer4);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer4);
    glBufferData(GL_ARRAY_BUFFER, normals4.size() * sizeof(glm::vec3), &normals4[0], GL_STATIC_DRAW);*/

    glUseProgram(programID);
    GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
    float x=0;
    float y=-3.5;


    do{//drawing loop where the whole game code will be isa
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

//------------------------------------------------------------------------------------------------------------------APPLE
        glm::mat4 RotationMatrix = eulerAngleYXZ(0.0f, 0.0f, 0.0f);//yaw, pitch and roll. Measured in radians
        glm::mat4 TranslationMatrix = translate(mat4(), vec3(0.0f,0.0f,0.0f));
        glm::mat4 ScalingMatrix = scale(mat4(), vec3(0.005f, 0.005f, 0.005f));
        glm::mat4 Model = TranslationMatrix*RotationMatrix * ScalingMatrix;

        glm::mat4 MVP        = Projection * View * Model;

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);

        glm::vec3 lightPos = glm::vec3(2,4,-4);
        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture);
        // Set our "myTextureSampler" sampler to user Texture Unit 0
        glUniform1i(TextureID, 0);

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(vertexPosition_modelspaceID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            vertexPosition_modelspaceID,  // The attribute we want to configure
            3,                            // size
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
        );

        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(vertexUVID);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
            vertexUVID,                   // The attribute we want to configure
            2,                            // size : U+V => 2
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
        );

        // 3rd attribute buffer : normals
        glEnableVertexAttribArray(vertexNormal_modelspaceID);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
            vertexNormal_modelspaceID,    // The attribute we want to configure
            3,                            // size
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
        );

        // Draw the triangles !
        glDrawArrays(GL_TRIANGLES, 0, vertices.size() );


//--------------------------------------------------------------------------------------------------------second Model(Box)
        glm::mat4 RotationMatrix1 = eulerAngleYXZ(0.0f, 0.0f, 0.0f);//yaw, pitch and roll. Measured in radians
        glm::mat4 TranslationMatrix1 = translate(mat4(), vec3(4.5f,3.0f,0.0f));
        glm::mat4 ScalingMatrix1 = scale(mat4(), vec3(0.5f, 0.5f, 0.5f));
        glm::mat4 Model1 = TranslationMatrix1*RotationMatrix1 * ScalingMatrix1;//order of multiplication is important (try different values above and different order of multiplication)

        glm::mat4 MVP1        = Projection * View * Model1;


        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP1[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model1[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);

        glm::vec3 lightPos1 = glm::vec3(0.5,1,-7.5);
        glUniform3f(LightID, lightPos1.x, lightPos1.y, lightPos1.z);

        glBindTexture(GL_TEXTURE_2D, Texture1);
        // Set our "myTextureSampler" sampler to user Texture Unit 0
        glUniform1i(TextureID, 0);

        // 1rst attribute buffer : vertices
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
        glVertexAttribPointer(
            vertexPosition_modelspaceID,  // The attribute we want to configure
            3,                            // size
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
        );

        // 2nd attribute buffer : UVs
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer1);
        glVertexAttribPointer(
            vertexUVID,                   // The attribute we want to configure
            2,                            // size : U+V => 2
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
        );

        //normals buffer
        //glEnableVertexAttribArray(vertexNormal_modelspaceID);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer1);
        glVertexAttribPointer(
            vertexNormal_modelspaceID,    // The attribute we want to configure
            3,                            // size
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
        );

        // Draw the triangles !
        glDrawArrays(GL_TRIANGLES, 0, vertices1.size() );

//****************************************************************************************second box
        glm::mat4 RotationMatrix11 = eulerAngleYXZ(0.0f, 0.0f, 0.0f);
        glm::mat4 TranslationMatrix11 = translate(mat4(), vec3(2.3,3.0f,0.0f));
        glm::mat4 ScalingMatrix11 = scale(mat4(), vec3(0.5f, 0.5f, 0.5f));
        glm::mat4 Model11 =  TranslationMatrix11 * RotationMatrix11 * ScalingMatrix11;

        glm::mat4 MVP11        = Projection * View * Model11;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP11[0][0]);
        glUniform3f(LightID, 2.3f, 0.0f, -8.5f);



        glDrawArrays(GL_TRIANGLES, 0, vertices1.size() );
//****************************************************************************************third box
        glm::mat4 RotationMatrix12 = eulerAngleYXZ(0.0f, 0.0f, 0.0f);
        glm::mat4 TranslationMatrix12 = translate(mat4(), vec3(0.0,3.0f,0.0f));
        glm::mat4 ScalingMatrix12 = scale(mat4(), vec3(0.5f, 0.5f, 0.5f));
        glm::mat4 Model12 =  TranslationMatrix12 * RotationMatrix12 * ScalingMatrix12;

        glm::mat4 MVP12        = Projection * View * Model12;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP12[0][0]);
        glUniform3f(LightID, 0.0f, 1.0f, -2.5f);


        glDrawArrays(GL_TRIANGLES, 0, vertices1.size() );
//****************************************************************************************fourth box
        glm::mat4 TranslationMatrix13 = translate(mat4(), vec3(-2.3,3.0f,0.0f));
        glm::mat4 Model13 =  TranslationMatrix13 * RotationMatrix12 * ScalingMatrix12;

        glm::mat4 MVP13        = Projection * View * Model13;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP13[0][0]);
        glUniform3f(LightID, 6.5f, -1.0f, -8.5f);


        glDrawArrays(GL_TRIANGLES, 0, vertices1.size() );

//****************************************************************************************fifth box
        glm::mat4 TranslationMatrix14 = translate(mat4(), vec3(-4.5,3.0f,0.0f));
        glm::mat4 Model14 =  TranslationMatrix14 * RotationMatrix12 * ScalingMatrix12;

        glm::mat4 MVP14        = Projection * View * Model14;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP14[0][0]);
        glUniform3f(LightID,8.5f, 1.0f, -7.5f);


        glDrawArrays(GL_TRIANGLES, 0, vertices1.size() );
        //****************************************************************************************sixth box
        glm::mat4 TranslationMatrix15 = translate(mat4(), vec3(-4.5,1.77f,0.0f));
        glm::mat4 Model15 =  TranslationMatrix15 * RotationMatrix12 * ScalingMatrix12;

        glm::mat4 MVP15        = Projection * View * Model15;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP15[0][0]);
        glUniform3f(LightID, 8.5f, 0.0f, -7.5f);


        glDrawArrays(GL_TRIANGLES, 0, vertices1.size() );
//****************************************************************************************7th box
        glm::mat4 TranslationMatrix16 = translate(mat4(), vec3(-2.3,1.77f,0.0f));
        glm::mat4 Model16 =  TranslationMatrix16 * RotationMatrix12 * ScalingMatrix12;

        glm::mat4 MVP16        = Projection * View * Model16;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP16[0][0]);
        glUniform3f(LightID, 6.5f, -1.0f, -8.5f);


        glDrawArrays(GL_TRIANGLES, 0, vertices1.size() );
//****************************************************************************************8th box
        glm::mat4 TranslationMatrix17 = translate(mat4(), vec3(0.0f,1.77f,0.0f));
        glm::mat4 Model17 =  TranslationMatrix17 * RotationMatrix12 * ScalingMatrix12;

        glm::mat4 MVP17        = Projection * View * Model17;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP17[0][0]);
        glUniform3f(LightID, 0.0f, 1.0f, -2.5f);


        glDrawArrays(GL_TRIANGLES, 0, vertices1.size() );
//****************************************************************************************9th box
        glm::mat4 TranslationMatrix18 = translate(mat4(), vec3(2.3f,1.77f,0.0f));
        glm::mat4 Model18 =  TranslationMatrix18 * RotationMatrix12 * ScalingMatrix12;

        glm::mat4 MVP18        = Projection * View * Model18;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP18[0][0]);
        glUniform3f(LightID, 2.3f, 0.23f, -8.5f);


        glDrawArrays(GL_TRIANGLES, 0, vertices1.size() );
//****************************************************************************************10th box
        glm::mat4 TranslationMatrix19 = translate(mat4(), vec3(4.5f,1.77f,0.0f));
        glm::mat4 Model19 =  TranslationMatrix19 * RotationMatrix12 * ScalingMatrix12;

        glm::mat4 MVP19        = Projection * View * Model19;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP19[0][0]);
        glUniform3f(LightID, 0.5f, 1.0f, -7.5f);



        glDrawArrays(GL_TRIANGLES, 0, vertices1.size() );
//*********************************************************************************************************BACKGROUND
        glm::mat4 RotationMatrixbg = eulerAngleYXZ(0.0f, 0.0f, 0.0f);
        glm::mat4 TranslationMatrixbg = translate(mat4(), vec3(0.0f,0.0f,10.0f));
        glm::mat4 ScalingMatrixbg = scale(mat4(), vec3(7.15f, 7.15f, 7.15f));
        glm::mat4 Modelbg =  TranslationMatrixbg * RotationMatrixbg * ScalingMatrixbg;

        glm::mat4 MVPbg        = Projection * View * Modelbg;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVPbg[0][0]);

        glBindTexture(GL_TEXTURE_2D, Texture4);
        // Set our "myTextureSampler" sampler to user Texture Unit 0
        glUniform1i(TextureID, 0);


        glDrawArrays(GL_TRIANGLES, 0, vertices1.size() );




//----------------------------------------------------------------------------------------------------third Model CocaCola Can
        glm::mat4 RotationMatrix2 = eulerAngleYXZ(0.0f, 0.0f, 0.0f);//yaw, pitch and roll. Measured in radians
        glm::mat4 TranslationMatrix2 = translate(mat4(), vec3(2.0f,0.0f,0.0f));
        glm::mat4 ScalingMatrix2 = scale(mat4(), vec3(0.2f, 0.2f, 0.2f));
        glm::mat4 Model2 = TranslationMatrix2*RotationMatrix2 * ScalingMatrix2;

        glm::mat4 MVP2        = Projection * View * Model2;

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP2[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model2[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);

        glm::vec3 lightPos2 = glm::vec3(0,4,-4);
        glUniform3f(LightID, lightPos2.x, lightPos2.y, lightPos2.z);

        // Bind our texture in Texture Unit 0
        glBindTexture(GL_TEXTURE_2D, Texture2);
        // Set our "myTextureSampler" sampler to user Texture Unit 0
        glUniform1i(TextureID, 0);

        // 1rst attribute buffer : vertices
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
        glVertexAttribPointer(
            vertexPosition_modelspaceID,  // The attribute we want to configure
            3,                            // size
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
        );

        // 2nd attribute buffer : UVs
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer2);
        glVertexAttribPointer(
            vertexUVID,                   // The attribute we want to configure
            2,                            // size : U+V => 2
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
        );
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer2);
        glVertexAttribPointer(
            vertexNormal_modelspaceID,    // The attribute we want to configure
            3,                            // size
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
        );

        // Draw the triangles !
        glDrawArrays(GL_TRIANGLES, 0, vertices2.size() );
//----------------------------------------------------------------------------------------------------fourth Model SPONGEPOP
        glm::mat4 RotationMatrix3 = eulerAngleYXZ(3.14f, 0.0f, 0.0f);//yaw, pitch and roll. Measured in radians
        glm::mat4 TranslationMatrix3 = translate(mat4(), vec3(x,-3.5f,0.0f));
        glm::mat4 ScalingMatrix3 = scale(mat4(), vec3(1.5f, 1.5f, 1.5f));
        glm::mat4 Model3 = TranslationMatrix3*RotationMatrix3 * ScalingMatrix3;

        if(glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS)
        {
            x-=0.1;
        }
        if(glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS)
        {
            x+=0.1;
        }

        glm::mat4 MVP3        = Projection * View * Model3;

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP3[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model3[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);

        glm::vec3 lightPos3 = glm::vec3(0,4,-4);
        glUniform3f(LightID, lightPos3.x, lightPos3.y, lightPos3.z);

        // Bind our texture in Texture Unit 0
        glBindTexture(GL_TEXTURE_2D, Texture3);
        // Set our "myTextureSampler" sampler to user Texture Unit 0
        glUniform1i(TextureID, 0);

        // 1rst attribute buffer : vertices
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer3);
        glVertexAttribPointer(
            vertexPosition_modelspaceID,  // The attribute we want to configure
            3,                            // size
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
        );

        // 2nd attribute buffer : UVs
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer3);
        glVertexAttribPointer(
            vertexUVID,                   // The attribute we want to configure
            2,                            // size : U+V => 2
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
        );

        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer3);
        glVertexAttribPointer(
            vertexNormal_modelspaceID,    // The attribute we want to configure
            3,                            // size
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
        );

        // Draw the triangles !
        glDrawArrays(GL_TRIANGLES, 0, vertices3.size() );
//----------------------------------------------------------------------------------------------------fifth Model KIWI
        /*glm::mat4 RotationMatrix4 = eulerAngleYXZ(0.0f, 0.0f, 1.57f);//yaw, pitch and roll. Measured in radians
        glm::mat4 TranslationMatrix4 = translate(mat4(), vec3(0.0f,0.0f,0.0f));
        glm::mat4 ScalingMatrix4 = scale(mat4(), vec3(1.f, 1.0f, 1.0f));
        glm::mat4 Model4 = TranslationMatrix4*RotationMatrix4 * ScalingMatrix4;//order of multiplication is important (try different values above and different order of multiplication)

        glm::mat4 MVP4        = Projection * View * Model4;

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP4[0][0]);

        // Bind our texture in Texture Unit 0
        glBindTexture(GL_TEXTURE_2D, Texture4);
        // Set our "myTextureSampler" sampler to user Texture Unit 0
        glUniform1i(TextureID, 0);

        // 1rst attribute buffer : vertices
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer4);
        glVertexAttribPointer(
            vertexPosition_modelspaceID,  // The attribute we want to configure
            3,                            // size
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
        );

        // 2nd attribute buffer : UVs
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer4);
        glVertexAttribPointer(
            vertexUVID,                   // The attribute we want to configure
            2,                            // size : U+V => 2
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
        );

        // Draw the triangles !
        glDrawArrays(GL_TRIANGLES, 0, vertices4.size() );*/









        glDisableVertexAttribArray(vertexPosition_modelspaceID);
        glDisableVertexAttribArray(vertexUVID);
        glDisableVertexAttribArray(vertexNormal_modelspaceID);
        glfwSwapBuffers();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
           glfwGetWindowParam( GLFW_OPENED ) );


    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteBuffers(1, &normalbuffer);

    glDeleteBuffers(1, &vertexbuffer1);
    glDeleteBuffers(1, &uvbuffer1);
    glDeleteBuffers(1, &normalbuffer1);

    glDeleteBuffers(1, &vertexbuffer2);
    glDeleteBuffers(1, &uvbuffer2);
    glDeleteBuffers(1, &normalbuffer2);

    glDeleteBuffers(1, &vertexbuffer3);
    glDeleteBuffers(1, &uvbuffer3);
    glDeleteBuffers(1, &normalbuffer3);

    glDeleteProgram(programID);
    glDeleteTextures(1, &TextureID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

