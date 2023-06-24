#include <jni.h>
#include <string>
 
using std::string;
 
class HelloFromCpp {
    string d_from;
    int d_number;
public:
    HelloFromCpp(const string& from, const int number)
        : d_from{ from }, d_number{ number } {}
    string get() {
        string r{};
        for (int i = 0; i < d_number; ++i) {
            r.append(d_from);
        }
        return r;
    }
};
 
extern "C" JNIEXPORT jstring JNICALL
Java_HelloFromCpp_bridge(JNIEnv *env, jobject, jstring s, jint i) {
    string native_from{ env->GetStringUTFChars(s, nullptr) };
    int native_number{ i };
     
    HelloFromCpp hello(native_from, native_number);
     
    return env->NewStringUTF(hello.get().c_str());
}
