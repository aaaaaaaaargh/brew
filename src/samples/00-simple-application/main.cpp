#include <brew/application/ApplicationListener.h>


#include "SampleConfig.h"

using namespace brew;

/**
 * The main listener that can be used to initialize the app.
 */
class MyApp : public ApplicationListener {
public:
    void onStart() override {
        getAppContext().log->stream("MyApp") << "Started";

        // This is where you would initialize the resources.
    }

    void onPause() override {
        getAppContext().log->stream("MyApp") << "Paused";
    }

    void onResume() override {
        getAppContext().log->stream("MyApp") << "Resumed";
    }

    void onQuit() override {
        getAppContext().log->stream("MyApp") << "Quit";
    }
};

int main() {
    LinuxApplicationConfig cfg;
    LinuxApplication app(std::make_unique<MyApp>(), cfg);

    app.start();
}