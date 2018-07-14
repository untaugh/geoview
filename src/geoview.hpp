#include <stdint.h>

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

class Geoview
{
public:
  Geoview();
  ~Geoview();
  uint32_t init();
  uint32_t run();

private:
  GLFWwindow *window;

  static Geoview *geoview; // used by static callbacks

  enum action {
    ACTION_BEGIN = 0x1,
    ACTION_DRAG = 0x2,
    ACTION_ROTATE = 0x4,
  };

  uint32_t actionflags = 0;
  float posx = 0.0;
  float posy = 0.0;
  float rotx = 0.0;
  float roty = 0.0;
  float zoom = 1.0;
  float cursorx = 0.0;
  float cursory = 0.0;

private:
  static void windowCloseCallback(GLFWwindow *window);
  static void mouseButtonCallBack(GLFWwindow *window, int button, int action, int mods);
  static void scrollCallBack(GLFWwindow *window, double x, double y);
  static void cursorPosCallBack(GLFWwindow *window, double x, double y);
};
