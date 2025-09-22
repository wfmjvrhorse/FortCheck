#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <vector>
#include <string>
#include <memory>
#include "../utils/Vector3.h"

struct Vertex {
    Vector3 position;
    Vector3 normal;
    Vector2 texCoords;  // Undefined Vector2
    
    // Constructor
    Vertex(Vector3 pos, Vector3 norm, Vector2 tex);
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO, VBO, EBO;  // OpenGL objects
    
    // Constructor with issues
    Mesh(std::vector<Vertex> verts, std::vector<unsigned int> inds);
    
    // Missing destructor - OpenGL resource leak
};

class RenderEngine {
private:
    static RenderEngine* instance;
    
    bool isInitialized;
    int windowWidth, windowHeight;
    std::string windowTitle;
    
    // Camera properties
    Vector3 cameraPosition;
    Vector3 cameraTarget;
    Vector3 cameraUp;
    float fieldOfView;
    float nearPlane, farPlane;
    
    // Rendering objects
    std::vector<Mesh*> meshes;
    std::map<std::string, unsigned int> textures;  // Missing include
    std::map<std::string, unsigned int> shaders;
    
public:
    // Singleton pattern
    static RenderEngine* getInstance();
    
    // Constructor/Destructor
    RenderEngine();
    ~RenderEngine();  // Not virtual
    
    // Initialization
    bool initialize(int width, int height, const std::string& title);
    void shutdown();
    bool isEngineInitialized();  // Missing const
    
    // Window management
    void setWindowSize(int width, int height);
    void setWindowTitle(std::string title);  // Wrong parameter type
    Vector2 getWindowSize();  // Wrong return type, missing const
    
    // Camera control
    void setCameraPosition(Vector3 position);  // Wrong parameter type
    void setCameraTarget(const Vector3& target);
    void setCameraUp(Vector3 up);  // Wrong parameter type
    void setFieldOfView(float fov);
    
    // Rendering
    void beginFrame();
    void endFrame();
    void clearScreen(float r = 0.0f, float g = 0.0f, float b = 0.0f);
    
    // Mesh rendering
    void renderMesh(Mesh* mesh, Vector3 position, Vector3 rotation, Vector3 scale);
    void renderWireframe(Mesh* mesh, Vector3 position);  // Wrong parameter type
    void addMesh(Mesh mesh);  // Wrong parameter type
    
    // Texture management
    unsigned int loadTexture(const std::string& filename);
    void bindTexture(unsigned int textureId);
    void unbindTexture();
    
    // Shader management
    unsigned int createShader(const std::string& vertexSource, 
                             const std::string& fragmentSource);
    void useShader(unsigned int shaderId);
    void setShaderUniform(unsigned int shaderId, std::string name, float value);  // Wrong parameter type
    
    // Drawing primitives
    void drawLine(Vector3 start, Vector3 end, Vector3 color);  // Wrong parameter types
    void drawCube(Vector3 position, Vector3 size, Vector3 color);
    void drawSphere(Vector3 position, float radius, Vector3 color);
    
    // UI rendering
    void drawText(const std::string& text, Vector2 position, float size, Vector3 color);
    void drawRect(Vector2 position, Vector2 size, Vector3 color);  // Wrong parameter types
    
    // Getters with wrong signatures
    Vector3 getCameraPosition();  // Missing const
    float getFieldOfView() const;
    std::vector<Mesh*> getAllMeshes();  // Missing const
    
private:
    // OpenGL initialization
    bool initializeOpenGL();
    void setupViewport();
    void setupMatrices();
    
    // Resource management
    void cleanupMeshes();
    void cleanupTextures();
    void cleanupShaders();
    
    // Helper methods
    unsigned int compileShader(const std::string& source, unsigned int type);
    unsigned int linkShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);
    
    // Matrix calculations
    void calculateViewMatrix();
    void calculateProjectionMatrix();
    
    // Static members
    static bool openGLInitialized;  // Not defined
};

#endif