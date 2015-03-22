#include <GL/glew.h>

 struct SkyboxShader {
        GLuint m_modelLocation;
        GLuint m_viewLocation;
        GLuint m_ProjectionLocation;
        GLuint m_skyboxTextureLocation;
        GLuint m_normalLocation;
        GLProgram m_program;

        SkyboxShader(){}
    };

    struct GBufferShader {
        GLuint m_modelLocation;
        GLuint m_viewLocation;
        GLuint m_ProjectionLocation;
        GLuint m_diffuseLocation;
        GLuint m_specularLocation;
        GLProgram m_program;

        GBufferShader(){}
    };

	struct BlitShader {
		GLuint m_modelLocation;
		GLuint m_viewLocation;
		GLuint m_ProjectionLocation;
		GLuint m_textureLocation;
		GLProgram m_program;

		BlitShader(){}
	};

	 struct AmbientLightShader {
        GLuint m_lightColorLocation;
        GLuint m_lightIntensityLocation;
        GLuint m_materialLocation;
        GLProgram m_program;

        AmbientLightShader(){}
    };

	struct PointLightShader {
		GLuint m_inverseViewProjectionLocation;
		GLuint m_lightPositionLocation;
		GLuint m_lightColorLocation;
		GLuint m_lightIntensityLocation;
		GLuint m_cameraPositionLocation;
		GLuint m_materialLocation;
		GLuint m_normalLocation;
		GLuint m_depthLocation;
		GLProgram m_program;

		PointLightShader(){}
	};
	

	struct DirectionalLightShader {
		GLuint m_inverseViewProjectionLocation;
		GLuint m_lightDirectionLocation;
		GLuint m_lightColorLocation;
		GLuint m_lightIntensityLocation;
		GLuint m_cameraPositionLocation;
        GLuint m_shadowBiasLocation;
        GLuint m_lightProjectionLocation;
        GLuint m_shadowSamplesLocation;
        GLuint m_shadowSampleSpreadLocation;
		GLuint m_materialLocation;
		GLuint m_normalLocation;
		GLuint m_depthLocation;
        GLuint m_shadowLocation;
		GLProgram m_program;

		DirectionalLightShader(){}
	};


	struct SpotLightShader {
		GLuint m_inverseViewProjectionLocation;
		GLuint m_lightPositionLocation;
		GLuint m_lightDirectionLocation;
		GLuint m_lightColorLocation;
		GLuint m_lightIntensityLocation;
		GLuint m_cameraPositionLocation;
        GLuint m_shadowBiasLocation;
        GLuint m_lightProjectionLocation;
		GLuint m_materialLocation;
		GLuint m_normalLocation;
		GLuint m_depthLocation;
        GLuint m_shadowLocation;
		GLProgram m_program;

		SpotLightShader(){}
	};


    struct ShadowShader {
        GLuint m_modelLocation;
        GLuint m_viewLocation;
        GLuint m_ProjectionLocation;
        GLProgram m_program;

        ShadowShader(){}
    };


    struct BlurShader {
        GLuint m_modelLocation;
        GLuint m_viewLocation;
        GLuint m_ProjectionLocation;
        GLuint m_textureLocation;
        GLuint m_sampleCountLocation;
        GLProgram m_program;

        BlurShader(){}
    };

    struct CocShader {
        GLuint m_modelLocation;
        GLuint m_viewLocation;
        GLuint m_ProjectionLocation;
        GLuint m_depthLocation;
        GLuint m_screenToViewLocation;
        GLuint m_focusLocation;
        GLProgram m_program;

        CocShader(){}
    };

    struct DofShader {
        GLuint m_modelLocation;
        GLuint m_viewLocation;
        GLuint m_ProjectionLocation;
        GLuint m_colorLocation;
        GLuint m_blurLocation;
        GLuint m_cocLocation;
        GLProgram m_program;

        DofShader(){}
    };