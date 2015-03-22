#include <Screen.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

bool elevated = false; 

void Screen::init(){
	m_window.setVerticalSyncEnabled(true);

	GLenum error;
    if ((error = glewInit()) != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(error));
    }

	// Projection matrix
    m_ProjectionMatrix = glm::perspective(45.f, m_window.getSize().x / (float) m_window.getSize().y, 0.1f, 1000.f);

    // music
    assert(m_music.openFromFile("../../assets/music/8bit.ogg"));
    m_music.play();


    // Load Shaders
    m_skyboxShader.m_program.load("../../shaders/skybox.vs.glsl", "../../shaders/skybox.fs.glsl");
    m_gbufferShader.m_program.load("../../shaders/gbuffer.vs.glsl", "../../shaders/gbuffer.fs.glsl");
    m_texturedMeshShader.m_program.load("../../shaders/gbuffer.vs.glsl", "../../shaders/texturedMesh.fs.glsl");
    m_blitShader.m_program.load("../../shaders/blit.vs.glsl", "../../shaders/blit.fs.glsl");    
    m_AmbientLightShader.m_program.load("../../shaders/blit.vs.glsl", "../../shaders/ambientLight.fs.glsl");
    m_pointLightShader.m_program.load("../../shaders/blit.vs.glsl", "../../shaders/pointLight.fs.glsl");
    m_directionalLightShader.m_program.load("../../shaders/blit.vs.glsl", "../../shaders/directionalLight.fs.glsl");
    m_cocShader.m_program.load("../../shaders/blit.vs.glsl","../../shaders/coc.fs.glsl");
    m_spotLightShader.m_program.load("../../shaders/blit.vs.glsl", "../../shaders/spotLight.fs.glsl");
    m_shadowShader.m_program.load("../../shaders/gbuffer.vs.glsl", "../../shaders/shadow.fs.glsl");
    m_blurShader.m_program.load("../../shaders/blit.vs.glsl","../../shaders/blur.fs.glsl"); 
    m_dofShader.m_program.load("../../shaders/blit.vs.glsl","../../shaders/dof.fs.glsl");

    // Set uniform locations
    m_skyboxShader.m_modelLocation = m_skyboxShader.m_program.getUniformLocation("Model");
    m_skyboxShader.m_viewLocation = m_skyboxShader.m_program.getUniformLocation("View");
    m_skyboxShader.m_ProjectionLocation = m_skyboxShader.m_program.getUniformLocation("Projection");
    m_skyboxShader.m_skyboxTextureLocation = m_skyboxShader.m_program.getUniformLocation("SkyboxTexture");
    m_skyboxShader.m_normalLocation = m_directionalLightShader.m_program.getUniformLocation("Normal");

	m_gbufferShader.m_modelLocation = m_gbufferShader.m_program.getUniformLocation("Model");
	m_gbufferShader.m_viewLocation = m_gbufferShader.m_program.getUniformLocation("View");
	m_gbufferShader.m_ProjectionLocation = m_gbufferShader.m_program.getUniformLocation("Projection");
	m_gbufferShader.m_diffuseLocation = m_gbufferShader.m_program.getUniformLocation("Diffuse");
	m_gbufferShader.m_specularLocation = m_gbufferShader.m_program.getUniformLocation("Specular");


    m_texturedMeshShader.m_modelLocation = m_texturedMeshShader.m_program.getUniformLocation("Model");
    m_texturedMeshShader.m_viewLocation = m_texturedMeshShader.m_program.getUniformLocation("View");
    m_texturedMeshShader.m_ProjectionLocation = m_texturedMeshShader.m_program.getUniformLocation("Projection");
    m_texturedMeshShader.m_diffuseLocation = m_texturedMeshShader.m_program.getUniformLocation("Diffuse");
    m_texturedMeshShader.m_specularLocation = m_texturedMeshShader.m_program.getUniformLocation("Specular");

    m_shadowShader.m_modelLocation = m_shadowShader.m_program.getUniformLocation("Model");
    m_shadowShader.m_viewLocation = m_shadowShader.m_program.getUniformLocation("View");
    m_shadowShader.m_ProjectionLocation = m_shadowShader.m_program.getUniformLocation("Projection");

	m_blitShader.m_modelLocation = m_blitShader.m_program.getUniformLocation("Model");
	m_blitShader.m_viewLocation = m_blitShader.m_program.getUniformLocation("View");
	m_blitShader.m_ProjectionLocation = m_blitShader.m_program.getUniformLocation("Projection");
	m_blitShader.m_textureLocation = m_blitShader.m_program.getUniformLocation("Texture");

    m_AmbientLightShader.m_lightColorLocation = m_AmbientLightShader.m_program.getUniformLocation("LightColor");
    m_AmbientLightShader.m_lightIntensityLocation = m_AmbientLightShader.m_program.getUniformLocation("LightIntensity");
    m_AmbientLightShader.m_materialLocation = m_AmbientLightShader.m_program.getUniformLocation("Material");

	m_pointLightShader.m_cameraPositionLocation = m_pointLightShader.m_program.getUniformLocation("CameraPosition");
	m_pointLightShader.m_inverseViewProjectionLocation = m_pointLightShader.m_program.getUniformLocation("InverseViewProjection");
	m_pointLightShader.m_lightPositionLocation = m_pointLightShader.m_program.getUniformLocation("LightPosition");
	m_pointLightShader.m_lightColorLocation = m_pointLightShader.m_program.getUniformLocation("LightColor");
	m_pointLightShader.m_lightIntensityLocation = m_pointLightShader.m_program.getUniformLocation("LightIntensity");
	m_pointLightShader.m_materialLocation = m_pointLightShader.m_program.getUniformLocation("Material");
	m_pointLightShader.m_normalLocation = m_pointLightShader.m_program.getUniformLocation("Normal");
	m_pointLightShader.m_depthLocation = m_pointLightShader.m_program.getUniformLocation("Depth");

	m_directionalLightShader.m_cameraPositionLocation = m_directionalLightShader.m_program.getUniformLocation("CameraPosition");
	m_directionalLightShader.m_inverseViewProjectionLocation = m_directionalLightShader.m_program.getUniformLocation("InverseViewProjection");
	m_directionalLightShader.m_lightDirectionLocation = m_directionalLightShader.m_program.getUniformLocation("LightDirection");
	m_directionalLightShader.m_lightColorLocation = m_directionalLightShader.m_program.getUniformLocation("LightColor");
	m_directionalLightShader.m_lightIntensityLocation = m_directionalLightShader.m_program.getUniformLocation("LightIntensity");
    m_directionalLightShader.m_lightProjectionLocation = m_directionalLightShader.m_program.getUniformLocation("LightProjection");
    m_directionalLightShader.m_shadowBiasLocation = m_directionalLightShader.m_program.getUniformLocation("ShadowBias");
    m_directionalLightShader.m_shadowSamplesLocation = m_directionalLightShader.m_program.getUniformLocation("ShadowSamples");
    m_directionalLightShader.m_shadowSampleSpreadLocation = m_directionalLightShader.m_program.getUniformLocation("ShadowSampleSpread");
	m_directionalLightShader.m_materialLocation = m_directionalLightShader.m_program.getUniformLocation("Material");
	m_directionalLightShader.m_normalLocation = m_directionalLightShader.m_program.getUniformLocation("Normal");
	m_directionalLightShader.m_depthLocation = m_directionalLightShader.m_program.getUniformLocation("Depth");
    m_directionalLightShader.m_shadowLocation = m_directionalLightShader.m_program.getUniformLocation("Shadow");

	m_spotLightShader.m_cameraPositionLocation = m_spotLightShader.m_program.getUniformLocation("CameraPosition");
	m_spotLightShader.m_inverseViewProjectionLocation = m_spotLightShader.m_program.getUniformLocation("InverseViewProjection");
    m_spotLightShader.m_lightPositionLocation = m_spotLightShader.m_program.getUniformLocation("LightPosition");
	m_spotLightShader.m_lightDirectionLocation = m_spotLightShader.m_program.getUniformLocation("LightDirection");
	m_spotLightShader.m_lightColorLocation = m_spotLightShader.m_program.getUniformLocation("LightColor");
	m_spotLightShader.m_lightIntensityLocation = m_spotLightShader.m_program.getUniformLocation("LightIntensity");
    m_spotLightShader.m_lightProjectionLocation = m_spotLightShader.m_program.getUniformLocation("LightProjection");
    m_spotLightShader.m_shadowBiasLocation = m_spotLightShader.m_program.getUniformLocation("ShadowBias");
	m_spotLightShader.m_materialLocation = m_spotLightShader.m_program.getUniformLocation("Material");
	m_spotLightShader.m_normalLocation = m_spotLightShader.m_program.getUniformLocation("Normal");
	m_spotLightShader.m_depthLocation = m_spotLightShader.m_program.getUniformLocation("Depth");
    m_spotLightShader.m_shadowLocation = m_spotLightShader.m_program.getUniformLocation("Shadow");

    m_blurShader.m_modelLocation = m_blurShader.m_program.getUniformLocation("Model");
    m_blurShader.m_viewLocation = m_blurShader.m_program.getUniformLocation("View");
    m_blurShader.m_ProjectionLocation = m_blurShader.m_program.getUniformLocation("Projection");
    m_blurShader.m_textureLocation = m_blurShader.m_program.getUniformLocation("Texture");
    m_blurShader.m_sampleCountLocation = m_blurShader.m_program.getUniformLocation("SampleCount");

    m_cocShader.m_modelLocation = m_cocShader.m_program.getUniformLocation("Model");
    m_cocShader.m_viewLocation = m_cocShader.m_program.getUniformLocation("View");
    m_cocShader.m_ProjectionLocation = m_cocShader.m_program.getUniformLocation("Projection");
    m_cocShader.m_screenToViewLocation = m_cocShader.m_program.getUniformLocation("ScreenToView");
    m_cocShader.m_depthLocation = m_cocShader.m_program.getUniformLocation("Depth");
    m_cocShader.m_focusLocation = m_cocShader.m_program.getUniformLocation("Focus");

    m_dofShader.m_modelLocation = m_dofShader.m_program.getUniformLocation("Model");
    m_dofShader.m_viewLocation = m_dofShader.m_program.getUniformLocation("View");
    m_dofShader.m_ProjectionLocation = m_dofShader.m_program.getUniformLocation("Projection");
    m_dofShader.m_colorLocation = m_dofShader.m_program.getUniformLocation("Color");
    m_dofShader.m_cocLocation = m_dofShader.m_program.getUniformLocation("CoC");
    m_dofShader.m_blurLocation = m_dofShader.m_program.getUniformLocation("Blur");


    m_skyboxTexture.load("../../assets/textures/skybox/",
                         "right.png",
                         "left.png",
                         "top.png",
                         "bottom.png",
                         "front.png",
                         "back.png");


	m_gbuffer.init(m_window.getSize().x, m_window.getSize().y); //init GBUFFER
    m_fxfbo.init(m_window.getSize().x, m_window.getSize().y); //post processing 
    m_shadowMapSpotLight.init(2048,2048);
    m_shadowMapDirectionnalLight.init(2048,2048);
    


    m_cube.init();
	m_blitPlane.init(1.f);
    m_terrain.load("../../assets/terrain.obj");
    m_star.load("../../assets/Textures/Mario's Star.obj");

    // model matrix
    m_terrainMatrix = glm::scale(m_modelMatrix, glm::vec3(0.01f));
    m_starPosition = glm::vec3(0,0,0);
    m_starRotationAxe = glm::vec3(0,1,0);
    m_starRotation = 0;

	// lights
    m_AmbientLight.init(glm::vec3(0.8f, 0.8f, 0.6f), 0.01f);
    m_directionalLight.init(glm::vec3(0.99,-1.93,-0.17), glm::vec3(0.4f, 0.3f, 1.f), .4f, 0.001f, 6, 1800);
    m_cameraPointLight.init(m_camera.getPosition(), glm::vec3(1, 1, 1), 4);
    m_starPointLight.init(glm::vec3(0, 3, -0.7f), glm::vec3(1, 1, 1), 12);
    m_starSpotLight.init(glm::vec3(1, -1, 0), glm::vec3(0, -1.0f, 0), glm::vec3(0.1f, 0.1f, 0.f), 1);

    //init trajectory points 

    trajectory[0] = glm::vec3(49.36,-5.5,17.37);
    trajectory[1] = glm::vec3(45.71,-5.5,12.61);
    trajectory[2] = glm::vec3(42.15,-1.97,8.27);
    trajectory[3] = glm::vec3(38.66,-5.81,4.21);
    trajectory[4] = glm::vec3(35.08,-5.01,-0.24);
    trajectory[5] = glm::vec3(31.36,-4.77,-4.94);
    trajectory[6] = glm::vec3(25.75,-6.77,-5.40);
    trajectory[7] = glm::vec3(19.69,-4.52,-6.06);
    trajectory[8] = glm::vec3(14.63,-5.88,-4.40);
    trajectory[9] = glm::vec3(9.35,-6.88,-1.42);
    trajectory[10] = glm::vec3(4.19,-4.95,2.04);
    trajectory[11] = glm::vec3(0.90, -7.05,5.00);
    trajectory[12] = glm::vec3(-6.46,-4.12,7.92);
    trajectory[13] = glm::vec3(-11.34,-4.62,11.44);
    trajectory[14] = glm::vec3(-14.16,-4.84,15.37);

    // Post processing
    m_focus = glm::vec3(0.f, 0.f, 0.f);
    m_sampleCount = 10.f;

    // Animation parameters
    m_animationSequence = 1;
    m_newSequence = 1;
    m_isInitiated = false;
    m_endSequence = false;

    
}

// Clear all information remaining in the buffers we use
void Screen::clearBuffers(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_gbuffer.bindFramebuffer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shadowMapDirectionnalLight.bindFramebuffer();
    glClear(GL_DEPTH_BUFFER_BIT);

    m_shadowMapSpotLight.bindFramebuffer();
    glClear(GL_DEPTH_BUFFER_BIT);

    for (unsigned int i = 0; i < 4; ++i){
        m_fxfbo.bindFramebufferWith(i);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

void Screen::gBufferPass(){
    // Enable Depth test
    glEnable(GL_DEPTH_TEST);

    // Set Viewport
    glViewport(0, 0, m_window.getSize().x, m_window.getSize().y);

	// Use gbuffer shaders
	m_gbufferShader.m_program.use();

	// Bind fbo
	m_gbuffer.bindFramebuffer();

    // Use mesh shader
    m_texturedMeshShader.m_program.use();


        // Send uniform data
        glUniform1i(m_texturedMeshShader.m_diffuseLocation, 0);
        glUniform1i(m_texturedMeshShader.m_specularLocation, 10);
        glUniformMatrix4fv(m_texturedMeshShader.m_modelLocation, 1, GL_FALSE, glm::value_ptr(m_terrainMatrix));
        glUniformMatrix4fv(m_texturedMeshShader.m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
        glUniformMatrix4fv(m_texturedMeshShader.m_ProjectionLocation, 1, GL_FALSE, glm::value_ptr(m_ProjectionMatrix));

        // Draw
        m_terrain.render();

   
        // Reset model matrix
        m_modelMatrix = glm::mat4(1.f);
        m_modelMatrix = glm::translate(m_modelMatrix, m_starPosition);
        m_modelMatrix = glm::rotate(m_modelMatrix, m_starRotation, m_starRotationAxe);
        m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(0.8f));

        // Send uniform data
        glUniform1i(m_texturedMeshShader.m_diffuseLocation, 0);
        glUniform1i(m_texturedMeshShader.m_specularLocation, 10);
        glUniformMatrix4fv(m_texturedMeshShader.m_modelLocation, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
        glUniformMatrix4fv(m_texturedMeshShader.m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
        glUniformMatrix4fv(m_texturedMeshShader.m_ProjectionLocation, 1, GL_FALSE, glm::value_ptr(m_ProjectionMatrix));

        // Draw
        m_star.render();
   

    // Unbind fbo
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Disable Depth test
    glDisable(GL_DEPTH_TEST);
}



void Screen::DrawSkybox(){
    m_fxfbo.bindFramebufferWith(0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_gbuffer.getTexture(2), 0);

    glEnable(GL_DEPTH_TEST);
    // Enable CULL FACE
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glDepthFunc(GL_LEQUAL);

    // Use gbuffer shaders
    m_skyboxShader.m_program.use();



    // Reset model matrix
    m_modelMatrix = glm::mat4(1.f);
    m_modelMatrix = glm::translate(m_modelMatrix, m_camera.getPosition());
    m_modelMatrix = glm::scale(m_modelMatrix,glm::vec3(20.f));

    // Send uniform data
    glUniform1i(m_skyboxShader.m_skyboxTextureLocation, 0);
    glUniform1i(m_skyboxShader.m_normalLocation, 1);
    glUniformMatrix4fv(m_skyboxShader.m_modelLocation, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
    glUniformMatrix4fv(m_skyboxShader.m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
    glUniformMatrix4fv(m_skyboxShader.m_ProjectionLocation, 1, GL_FALSE, glm::value_ptr(m_ProjectionMatrix));

    // Bind textures
    m_skyboxTexture.bind(GL_TEXTURE0);

    // Draw
    m_cube.render();


    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    // Unbind fbo
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Screen::playNewSequence(){
    m_animationSequence = m_newSequence;
    m_isInitiated = false;
}

void Screen::outoftube(const float elapsedTime){
    if (!m_isInitiated){

        // Camera
        m_camera.setPosition(glm::vec3(55, 4.5f, 25.f));
        m_cameraPointLight.setPosition(m_camera.getPosition());
        m_cameraPointLight.setIntensity(5.f);
        m_camera.setPhi(30);
        m_camera.setTheta(-7);

        //star
        m_starPosition = glm::vec3(58.7,2.f, 31.25f);
        m_starRotation = 180; 
        m_focus = glm::vec3(2,1,20);

        // Speed
        m_speed = 15.f;
        m_speed2 = 0.3f;

        m_isInitiated = true;

        
    }
     glm::vec3 B = glm::vec3(54.28,-4.77,23.49); 
    glm::vec3 dir = B - glm::vec3(58.7,4.5f, 31.25f);
    m_cameraPointLight.setPosition(m_camera.getPosition());
    m_starPointLight.setPosition(m_starPosition); 
    m_starSpotLight.setPosition(m_starPosition); 

    if(m_starPosition.y < 4.5f && !elevated) {m_starPosition.y += m_speed2 * elapsedTime; } 
    else { // the star is up enough 
        elevated = true;
        if(m_starPosition.y > B.y) m_starPosition += elapsedTime * dir;
        else {
            m_isInitiated = false;
            m_endSequence = true;
        }
        
    } 

}


void Screen::Travelling1(const float elapsedTime){
    if (!m_isInitiated){

       
        // Camera
        m_camera.setPosition(glm::vec3(41.29, -1.73f, 28.86f));
        m_cameraPointLight.setPosition(m_camera.getPosition());
        m_cameraPointLight.setIntensity(5.f);
        m_camera.setPhi(133);
        m_camera.setTheta(-13);

        //star
        m_starPosition = glm::vec3(54.28,-4.77,23.49); 
        m_starRotation = 180; 
        index = 0;

        // Fx
        m_focus = glm::vec3(0,1,30);

        // Speed
        m_speed = 15.f;

        m_isInitiated = true;
        timer = 0; 

        
    }
    glm::vec3 B = glm::vec3(15.72,-1.73f,1.43); 
    glm::vec3 dir = B - glm::vec3(41.29, -1.73f, 28.86f);
    m_cameraPointLight.setPosition(m_camera.getPosition());
    m_starPointLight.setPosition(m_starPosition); 
    m_starSpotLight.setPosition(m_starPosition); 
    glm::vec3 dir2 = glm::vec3(0,0,0);


    if(index == 0) {
        dir2 = trajectory[index] - glm::vec3(54.28,-4.77,23.49);
        if(fabs(m_starPosition.x - trajectory[index].x ) < 0.1 ) { index++; }
    }
    else if(index > 0 && index < 15) {
        dir2 = trajectory[index] - trajectory[index-1];
         if(fabs(m_starPosition.x - trajectory[index].x ) < 0.1   ) { index++; }
    }
    else dir2 = glm::vec3(0);
    m_starPosition += (elapsedTime* 1.5f) * dir2 ;
    //std::cout << index << " : " << m_starPosition.x - trajectory[index].x << std::endl; 

    if(m_camera.getPosition().x > B.x || m_camera.getPosition().z > B.z)  { 
       m_camera.setPosition(m_camera.getPosition() +( elapsedTime * 0.2f) * dir ) ; 
        

    }
    else timer += elapsedTime;
    if(timer > 4) {
           m_isInitiated = false;
            m_endSequence = true;
    } 
        
        
   

}

void Screen::starcross(const float elapsedTime){
    if (!m_isInitiated){

       
        // Camera
        m_camera.setPosition(glm::vec3(-14.11,-7.97,13.64));
        m_cameraPointLight.setPosition(m_camera.getPosition());
        m_cameraPointLight.setIntensity(5.f);
        m_camera.setPhi(128);
        m_camera.setTheta(67);

        //star
        m_starPosition = trajectory[13];
        m_starRotation = 180; 


        // Fx
        m_focus = glm::vec3(0,1,30);

        // Speed
        m_speed = 15.f;

        m_isInitiated = true;

        timer = 0; 

        
    }
   
    m_cameraPointLight.setPosition(m_camera.getPosition());
    m_starPointLight.setPosition(m_starPosition); 
    m_starSpotLight.setPosition(m_starPosition); 
    glm::vec3 dir2 = glm::vec3(0,0,0);
    dir2 = trajectory[14] - trajectory[13];
    
    m_starPosition += (elapsedTime* 1.5f) * dir2 ;

    //std::cout << timer << std::endl; 
    timer += elapsedTime; 
    

        if(timer > 4 ) {
            m_isInitiated = false;
            m_endSequence = true; 

        }     
   

}

void Screen::lookingup(const float elapsedTime){
    if (!m_isInitiated){

       
        // Camera
        m_camera.setPosition(glm::vec3(-9.87,-5.85,14.98));
        m_cameraPointLight.setPosition(m_camera.getPosition());
        m_cameraPointLight.setIntensity(5.f);
        m_camera.setPhi(280);
        m_camera.setTheta(10);

        //star
        m_starPosition = trajectory[14] + glm::vec3(0.8,0,0.8);
        m_starRotation = -10; 

        



        // Fx
        m_focus = glm::vec3(0,1,30);

        // Speed
        m_speed = 5.f;

        m_isInitiated = true;

        
    }
   glm::vec3 dir = glm::vec3(-19.65,5,23.42) - trajectory[14]  + glm::vec3(0.8,0,0.8);;
    m_cameraPointLight.setPosition(m_camera.getPosition());
    m_starPointLight.setPosition(m_starPosition); 
    m_starSpotLight.setPosition(m_starPosition); 
    m_starPosition += (elapsedTime* 0.2f) * dir ;

    //end phi 313 end theta 26 
    if(m_camera.getPhi() < 313 && m_camera.getTheta()<26 ) { 
        if(m_camera.getPhi() < 313) m_camera.rotatePhi(m_speed*elapsedTime);
        if(m_camera.getTheta()  <26) m_camera.rotateTheta(m_speed*elapsedTime);
       


     }
     else {

        m_isInitiated = false;
        m_endSequence = true; 

     }       
   

}

void Screen::downtube(const float elapsedTime){
    if (!m_isInitiated){

       
        // Camera
        m_camera.setPosition(glm::vec3(-28.44,8.06,24.48));
        m_cameraPointLight.setPosition(m_camera.getPosition());
        m_cameraPointLight.setIntensity(5.f);
        m_camera.setPhi(454);
        m_camera.setTheta(-33);

        //star
        m_starPosition = glm::vec3(-19.65,5.13,23.42);
        m_starRotation = -10; 

        
        // Fx
        m_focus = glm::vec3(0,1,30);

        // Speed
        m_speed = 5.f;

        m_isInitiated = true;

        timer = 0; 

        
    }
   glm::vec3 dir = glm::vec3(-19.65,5,23.42) - trajectory[14]  + glm::vec3(0.8,0,0.8);;
    m_cameraPointLight.setPosition(m_camera.getPosition());
    m_starPointLight.setPosition(m_starPosition); 
    m_starSpotLight.setPosition(m_starPosition); 
    if(m_starPosition.y > -2) m_starPosition.y -= (elapsedTime* 2.f) ;
    else {
         m_starSpotLight.setIntensity(0);
         m_starPointLight.setIntensity(0);
         timer += elapsedTime;
         
         if(timer > 4){
                m_isInitiated = false;
                m_endSequence = true; }

     }       
   

}

void Screen::upstar(const float elapsedTime){
    if (!m_isInitiated){

        m_camera.setPosition(glm::vec3(-28.44,8.06,24.48));
        m_cameraPointLight.setPosition(m_camera.getPosition());
        m_cameraPointLight.setIntensity(5.f);
        m_camera.setPhi(454);
        m_camera.setTheta(-33);
        m_starPosition = glm::vec3(-19.65,-4,23.42);
        m_starRotation = -10; 
        m_starPointLight.setIntensity(12); 
        m_focus = glm::vec3(0,1,30);
        m_speed = 5.f;
        m_isInitiated = true;
        timer = 0;       
    }
   glm::vec3 dir = glm::vec3(-19.65,5,23.42) - trajectory[14]  + glm::vec3(0.8,0,0.8);;
    m_cameraPointLight.setPosition(m_camera.getPosition());
    m_starPointLight.setPosition(m_starPosition); 
    m_starSpotLight.setPosition(m_starPosition); 
    m_starRotation += elapsedTime * 100; 
    timer += elapsedTime;

    if(m_camera.getTheta() < 85) m_camera.rotateTheta(m_speed*elapsedTime);
    if(m_starPosition.y < 100) m_starPosition.y += (elapsedTime* 2.f) ;
    else {
         
         if(timer > 7){
            std::cout << " THE END..." << std::endl;
            running = false; 
         }

     }       
   

}

void Screen::animation(const float elapsedTime){
    switch(m_animationSequence){
        case 1:
            outoftube(elapsedTime);
            break;
        case 2:
            Travelling1(elapsedTime);
            break;    
        case 3:
            starcross(elapsedTime);
            break;  
        case 4:
            lookingup(elapsedTime);
            break; 
        case 5:
            downtube(elapsedTime);
            break; 
        case 6:
            upstar(elapsedTime);   
            break; 


    }

    if (m_endSequence) {
        m_animationSequence++;
        m_endSequence = false;
    }
}


void Screen::run(){
    sf::Clock clock;
    float elapsedTime = 0.f;

	m_prevMousePosition = sf::Mouse::getPosition(m_window);

    // main loop
    running = true;
    while (running)
    {
        elapsedTime = clock.restart().asSeconds();
        m_fps = 1.f/ elapsedTime;

        sf::Event event;
        while (m_window.pollEvent(event))
        {
            int handled =  0 ; 
            if(!handled)
            {
                if (event.type == sf::Event::Closed)
                {
                    running = false;
                }
                else if (event.type == sf::Event::Resized)
                {
                    glViewport(0, 0, event.size.width, event.size.height);
                }
                else if (event.type == sf::Event::KeyPressed){
                    // Show the deffered PRESS A
                    if (event.key.code == sf::Keyboard::A){
                        m_showdeferred = !m_showdeferred;
                    }
                }
            }
        }

    animation(elapsedTime);
    m_camera.AngleToSphere();
    m_viewMatrix = m_camera.getViewMatrix();
    clearBuffers();

    /////////////// GEOMETRY PASS

    gBufferPass();


   ///////////////// DIRECTIONAL SHADOWMAPPING

    // Enable Depth test
    glEnable(GL_DEPTH_TEST);

    // Use gbuffer shaders
    m_shadowShader.m_program.use();

    // Bind fbo
    m_shadowMapDirectionnalLight.bindFramebuffer();

    // Set Viewport
    glViewport(0, 0, 2048, 2048);

    // Send uniform data
    glUniformMatrix4fv(m_shadowShader.m_ProjectionLocation, 1, 0, glm::value_ptr(m_directionalLight.getLightToShadowMap()));
    glUniformMatrix4fv(m_shadowShader.m_viewLocation, 1, 0, glm::value_ptr(m_directionalLight.getWorldToLight())); 
    glUniformMatrix4fv(m_shadowShader.m_modelLocation, 1, 0, glm::value_ptr(m_terrainMatrix));

    // Draw
    m_terrain.render();

    // Reset model matrix
    m_modelMatrix = glm::mat4(1.f);
    m_modelMatrix = glm::translate(m_modelMatrix, m_starPosition);
    m_modelMatrix = glm::rotate(m_modelMatrix, m_starRotation, m_starRotationAxe);
    m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(0.8f));


    // Send uniform data
    glUniformMatrix4fv(m_shadowShader.m_modelLocation, 1, 0, glm::value_ptr(m_modelMatrix));

    // Draw
    m_star.render();
      
    // Unbind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Disable Depth test
    glDisable(GL_DEPTH_TEST);

    glViewport(0, 0, m_window.getSize().x, m_window.getSize().y);



   ///////////////SPOTLIGHT SHADOWMAPPING

    // Enable Depth test
    glEnable(GL_DEPTH_TEST);

    // Use gbuffer shaders
    m_shadowShader.m_program.use();

    // Bind fbo
    m_shadowMapSpotLight.bindFramebuffer();

    // Set Viewport
    glViewport(0, 0, 1024, 1024);

    // Update shadowmatrices
    m_starSpotLight.setShadowMatrices();

    // Send uniform data
    glUniformMatrix4fv(m_shadowShader.m_ProjectionLocation, 1, 0, glm::value_ptr(m_starSpotLight.getLightToShadowMap()));
    glUniformMatrix4fv(m_shadowShader.m_viewLocation, 1, 0, glm::value_ptr(m_starSpotLight.getWorldToLight()));
    glUniformMatrix4fv(m_shadowShader.m_modelLocation, 1, 0, glm::value_ptr(m_terrainMatrix));

    // Draw
    m_terrain.render();

    // Reset model matrix
    m_modelMatrix = glm::mat4(1.f);
    m_modelMatrix = glm::translate(m_modelMatrix, m_starPosition);
    m_modelMatrix = glm::rotate(m_modelMatrix, m_starRotation, m_starRotationAxe);
    m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(0.8f));


    // Send uniform data
    glUniformMatrix4fv(m_shadowShader.m_modelLocation, 1, 0, glm::value_ptr(m_modelMatrix));

    // Draw
    m_star.render();

    // Unbind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Disable Depth test
    glDisable(GL_DEPTH_TEST);

    glViewport(0, 0, m_window.getSize().x, m_window.getSize().y);






    ////////////LIGHTNINGPASS

    m_fxfbo.bindFramebufferWith(0);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);

    // Use pointLight shaders
    m_AmbientLightShader.m_program.use();

    // Send uniform value
    glUniform1i(m_AmbientLightShader.m_materialLocation, 0);

    glUniform3fv(m_AmbientLightShader.m_lightColorLocation, 1, glm::value_ptr(m_AmbientLight.getColor()));
    glUniform1f(m_AmbientLightShader.m_lightIntensityLocation, m_AmbientLight.getIntensity());

    // Bind textures : material
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(0));

    m_blitPlane.render();
      

    // Use directionalLight shaders
    m_directionalLightShader.m_program.use();

    // Send uniform value
    glUniform1i(m_directionalLightShader.m_materialLocation, 0);
    glUniform1i(m_directionalLightShader.m_normalLocation, 1);
    glUniform1i(m_directionalLightShader.m_depthLocation, 2);
    glUniform1i(m_directionalLightShader.m_shadowLocation, 3);

    glm::mat4 inverseViewProjection = glm::transpose(glm::inverse(m_ProjectionMatrix * m_viewMatrix));

    glUniform3fv(m_directionalLightShader.m_cameraPositionLocation, 1, glm::value_ptr(m_camera.getPosition()));
    glUniformMatrix4fv(m_directionalLightShader.m_inverseViewProjectionLocation, 1, 0, glm::value_ptr(inverseViewProjection));

    glUniform3fv(m_directionalLightShader.m_lightDirectionLocation, 1, glm::value_ptr(m_directionalLight.getDirection()));
    glUniform3fv(m_directionalLightShader.m_lightColorLocation, 1, glm::value_ptr(m_directionalLight.getColor()));
    glUniform1f(m_directionalLightShader.m_lightIntensityLocation, m_directionalLight.getIntensity());
    glUniformMatrix4fv(m_directionalLightShader.m_lightProjectionLocation, 1, 0, glm::value_ptr(m_directionalLight.getWorldToShadowMap()));
    glUniform1f(m_directionalLightShader.m_shadowBiasLocation, m_directionalLight.getShadowBias());
    glUniform1f(m_directionalLightShader.m_shadowSamplesLocation, m_directionalLight.getShadowSamples());
    glUniform1f(m_directionalLightShader.m_shadowSampleSpreadLocation, m_directionalLight.getShadowSampleSpread());

    // Bind textures : material, normal, depth and shadow
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(0));
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(1));
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(2));
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, m_shadowMapDirectionnalLight.getTexture());

    m_blitPlane.render();


    // Use pointLight shaders
    m_pointLightShader.m_program.use();

    // Send uniform value
    glUniform1i(m_pointLightShader.m_materialLocation, 0);
    glUniform1i(m_pointLightShader.m_normalLocation, 1);
    glUniform1i(m_pointLightShader.m_depthLocation, 2);

    // Bind textures : material, normal and depth
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(0));
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(1));
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(2));

    inverseViewProjection = glm::transpose(glm::inverse(m_ProjectionMatrix * m_viewMatrix));

    glUniform3fv(m_pointLightShader.m_cameraPositionLocation, 1, glm::value_ptr(m_camera.getPosition()));
    glUniformMatrix4fv(m_pointLightShader.m_inverseViewProjectionLocation, 1, 0, glm::value_ptr(inverseViewProjection));

 
    // Calculate new position of starPointLight
    m_modelMatrix = glm::mat4(1.f);
    m_modelMatrix = glm::translate(m_modelMatrix, m_starPosition);
    m_modelMatrix = glm::rotate(m_modelMatrix, m_starRotation, m_starRotationAxe);
    m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(0,3,0));
    glm::vec4 m_newPosition = m_modelMatrix * glm::vec4(0,0,0,1);
    m_starPointLight.setPosition(glm::vec3(m_newPosition.x, m_newPosition.y, m_newPosition.z));

    glUniform3fv(m_pointLightShader.m_lightPositionLocation, 1, glm::value_ptr(m_starPointLight.getPosition()));
    glUniform3fv(m_pointLightShader.m_lightColorLocation, 1, glm::value_ptr(m_starPointLight.getColor()));
    glUniform1f(m_pointLightShader.m_lightIntensityLocation, m_starPointLight.getIntensity());

    m_blitPlane.render();


    glUniform3fv(m_pointLightShader.m_lightPositionLocation, 1, glm::value_ptr(m_cameraPointLight.getPosition()));
    glUniform3fv(m_pointLightShader.m_lightColorLocation, 1, glm::value_ptr(m_cameraPointLight.getColor()));
    glUniform1f(m_pointLightShader.m_lightIntensityLocation, m_cameraPointLight.getIntensity());

    m_blitPlane.render();


    // Use spotLight shaders
    m_spotLightShader.m_program.use();


    // Send uniform value
    glUniform1i(m_spotLightShader.m_materialLocation, 0);
    glUniform1i(m_spotLightShader.m_normalLocation, 1);
    glUniform1i(m_spotLightShader.m_depthLocation, 2);
    glUniform1i(m_spotLightShader.m_shadowLocation, 3);

    inverseViewProjection = glm::transpose(glm::inverse(m_ProjectionMatrix * m_viewMatrix));

    glUniform3fv(m_spotLightShader.m_cameraPositionLocation, 1, glm::value_ptr(m_camera.getPosition()));
    glUniformMatrix4fv(m_spotLightShader.m_inverseViewProjectionLocation, 1, 0, glm::value_ptr(inverseViewProjection));

    glUniform3fv(m_spotLightShader.m_lightDirectionLocation, 1, glm::value_ptr(m_starSpotLight.getDirection()));
    glUniform3fv(m_spotLightShader.m_lightPositionLocation, 1, glm::value_ptr(m_starSpotLight.getPosition()));
    glUniform3fv(m_spotLightShader.m_lightColorLocation, 1, glm::value_ptr(m_starSpotLight.getColor()));
    glUniform1f(m_spotLightShader.m_lightIntensityLocation, m_starSpotLight.getIntensity());
    glUniformMatrix4fv(m_spotLightShader.m_lightProjectionLocation, 1, 0, glm::value_ptr(m_starSpotLight.getWorldToShadowMap()));
    glUniform1f(m_spotLightShader.m_shadowBiasLocation, 0.001f);


    // Bind textures : material, normal, depth and shadow
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(0));
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(1));
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(2));
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, m_shadowMapSpotLight.getTexture());

    m_blitPlane.render();


    glDisable(GL_BLEND);

    // Unbind fbo
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    DrawSkybox();


    ////////////POST PROCESSING

     m_fxfbo.bindFramebufferWith(1);

    glViewport(0, 0, m_window.getSize().x, m_window.getSize().y);

    m_screenToView = glm::inverse(m_ProjectionMatrix);

    // Use coc shaders
    m_cocShader.m_program.use();

    glUniform1i(m_cocShader.m_depthLocation, 0);
    glUniform3fv(m_cocShader.m_focusLocation,1, glm::value_ptr(m_focus));
    glUniformMatrix4fv(m_cocShader.m_modelLocation, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
    glUniformMatrix4fv(m_cocShader.m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
    glUniformMatrix4fv(m_cocShader.m_ProjectionLocation, 1, GL_FALSE, glm::value_ptr(m_ProjectionMatrix));
    glUniformMatrix4fv(m_cocShader.m_screenToViewLocation, 1, GL_FALSE, glm::value_ptr(m_screenToView));

    // Bind depth texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(2));

    m_blitPlane.render();

    m_fxfbo.bindFramebufferWith(2);

    glViewport(0, 0, m_window.getSize().x / 2, m_window.getSize().y / 2);

    // Use blur shaders
    m_blurShader.m_program.use();

    glUniform1i(m_blurShader.m_textureLocation, 0);
    glUniform1f(m_blurShader.m_sampleCountLocation, m_sampleCount);
    glUniformMatrix4fv(m_blurShader.m_modelLocation, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
    glUniformMatrix4fv(m_blurShader.m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
    glUniformMatrix4fv(m_blurShader.m_ProjectionLocation, 1, GL_FALSE, glm::value_ptr(m_ProjectionMatrix));

    // Bind depth texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_fxfbo.getTexture(0));

    m_blitPlane.render();

   
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport(0, 0, m_window.getSize().x, m_window.getSize().y);

    m_dofShader.m_program.use();
    glUniform1i(m_dofShader.m_colorLocation, 0);
    glUniform1i(m_dofShader.m_blurLocation, 1);
    glUniform1i(m_dofShader.m_cocLocation, 2);
    glUniformMatrix4fv(m_dofShader.m_modelLocation, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
    glUniformMatrix4fv(m_dofShader.m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
    glUniformMatrix4fv(m_dofShader.m_ProjectionLocation, 1, GL_FALSE, glm::value_ptr(m_ProjectionMatrix));

    // Bind textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_fxfbo.getTexture(0));
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_fxfbo.getTexture(2));
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, m_fxfbo.getTexture(1));

    m_blitPlane.render();

    // Debind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

        if (m_showdeferred){
            
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            m_blitShader.m_program.use();
            glUniform1i(m_blitShader.m_textureLocation, 0);

            //diffuse
            glViewport(0, 0, m_window.getSize().x/5, m_window.getSize().y/5);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(0));
            m_blitPlane.render();

            //Normal
            glViewport(m_window.getSize().x/5, 0, m_window.getSize().x/5, m_window.getSize().y/5);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(1));
            m_blitPlane.render();

            //Depth
            glViewport(2*m_window.getSize().x/5, 0, m_window.getSize().x/5, m_window.getSize().y/5);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_gbuffer.getTexture(2));
            m_blitPlane.render();

            //Shadowmap
            glViewport(3*m_window.getSize().x/5, 0, m_window.getSize().x/5, m_window.getSize().y/5);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_shadowMapSpotLight.getTexture());
            m_blitPlane.render();


            //COC
            glViewport(4*m_window.getSize().x/5, 0, m_window.getSize().x/5, m_window.getSize().y/5);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_fxfbo.getTexture(1));
            m_blitPlane.render();
        }

        m_window.display();
    }
}
