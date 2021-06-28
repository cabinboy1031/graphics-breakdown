#ifndef __VIOLET_ENTRYPOINT_H_
#define __VIOLET_ENTRYPOINT_H_

extern Violet::Application* Violet::CreateApplication();

int main(int argc, char** argv){
    auto *app = Violet::CreateApplication();
    app->run();
    delete app;
}

#endif // __ENTRYPOINT_H_
