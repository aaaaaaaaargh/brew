#include <jni.h>
#include <string>

#include <brew/core/SystemInfo.h>

extern "C"
JNIEXPORT jstring

JNICALL
Java_brew_randomaccess_de_brewapp_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    auto str = brew::SystemInfo::getPlatformName();
    return env->NewStringUTF(str.c_str());
}
