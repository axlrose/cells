/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <jni.h>
#include <fcntl.h>
#include <android/log.h>
#include <errno.h>
#include <dirent.h>

#define I2CNAME "/sys/bus/i2c/devices/0-0019/name"
#define CPUINFO "/proc/cpuinfo"

/*========================*/
#define LOG_TAG "chendong"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
/*========================*/


/*
 *读指定路径下的文件的内容
 *参数:
 *	path:路径
 *	data:返回的字符串
 *	data_len:字符串空间的长度
 *
 *返回值：
 *	读到的个数或是错误号
 * */
static int read_path_string(char const * path, char *data, int data_len)
{
	int nbytes;
	int fd;

	if (path == NULL)
		return -1;

	fd = open(path, O_RDONLY);
	if (fd < 0) {
		nbytes = -errno;
		goto fail;
	}
	nbytes = read(fd, data, data_len - 1);
	if (-1 == nbytes) {
		nbytes = -errno;
		close(fd);
		goto fail;
	}
	close(fd);
	data[nbytes] = '\0';
fail:
	return nbytes;
}

/*
 *读指定文件的内容，并把返回的字符串转化为整型
 *
 * */
static int read_path_int(char const * path)
{
	int fd;
	if (path == NULL)
		return -1;

	fd = open(path, O_RDWR);
	if (fd >= 0) {
		char buffer[20];
		int ret = read(fd, buffer, sizeof(int));
		close(fd);
		return ret == -1 ? -errno : atoi(buffer);
	}
	return -errno;
}

static char buf[1000];
jstring
Java_com_example_hellojni_HelloJni_stringFromJNI( JNIEnv* env,
                                                  jobject thiz )
{
	read_path_string(CPUINFO, buf, sizeof(buf));
    return (*env)->NewStringUTF(env, buf);
}
