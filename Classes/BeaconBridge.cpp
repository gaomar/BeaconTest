//
//  BeaconBridge.cpp
//  BeaconTest-mobile
//
//  Created by Takauma on 2017/09/04.
//

#include "BeaconBridge.hpp"
#include "platform/android/jni/JniHelper.h"
#define  CLASS_NAME "org/cocos2dx/cpp/AppActivity"

static BeaconCallback _beaconCallback;

void BeaconBridge::beaconAction(bool flg, BeaconCallback callback)
{
    _beaconCallback = nullptr;
    _beaconCallback = callback;
    
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "beaconAction", "(Z)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, flg);
        
        // 解放
        t.env->DeleteLocalRef(t.classID);
    }
}

void BeaconBridge::initBeacon(const std::string& uuid)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "initBeacon", "(Ljava/lang/String;)V")) {
        jstring aUUID = t.env->NewStringUTF(uuid.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, aUUID);
        
        // 解放
        t.env->DeleteLocalRef(aUUID);
        t.env->DeleteLocalRef(t.classID);
    }
}

std::string BeaconBridge::initBeaconUUID()
{
    std::string ret;
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "initBeaconUUID", "()Ljava/lang/String;")) {
        jstring jStr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        const char* str = t.env->GetStringUTFChars(jStr, NULL);
        ret = str;
        
        t.env->ReleaseStringUTFChars(jStr,str);
        t.env->DeleteLocalRef(t.classID);
    }
    
    return ret;
    
}


extern "C"
{
    void Java_org_cocos2dx_cpp_AppActivity_beaconActionCallback(JNIEnv *env, jobject thiz, jboolean flg)
    {
        if (_beaconCallback) _beaconCallback(flg);
    }
}
