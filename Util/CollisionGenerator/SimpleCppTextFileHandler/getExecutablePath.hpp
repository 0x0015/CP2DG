#pragma once
#include <string>

#ifdef _WIN32
#include <stdlib.h>
    #elif _WIN64
#include <stdlib.h>
    #elif __APPLE__ || __MACH__
#include <mach-o/dyld.h>
    #elif __linux__
#include <unistd.h>
#include <limits.h>
    #elif __FreeBSD__
#include <sys/types.h>
#include <sys/sysctl.h>
    #endif
/*
 * Returns the full path to the currently running executable,
 * or an empty string in case of failure.
 */
std::string getExecutablePath() {
    #ifdef _WIN32
        char *exePath;
        if (_get_pgmptr(&exePath) != 0)
            exePath = "";
    #elif _WIN64
        char *exePath;
        if (_get_pgmptr(&exePath) != 0)
            exePath = "";
    #elif __linux__
        char exePath[PATH_MAX];
        ssize_t len = ::readlink("/proc/self/exe", exePath, sizeof(exePath));
        if (len == -1 || len == sizeof(exePath))
            len = 0;
        exePath[len] = '\0';
    #elif __APPLE__ || __MACH__
        char exePath[PATH_MAX];
        uint32_t len = sizeof(exePath);
        if (_NSGetExecutablePath(exePath, &len) != 0) {
            exePath[0] = '\0'; // buffer too small (!)
        } else {
            // resolve symlinks, ., .. if possible
            char *canonicalPath = realpath(exePath, NULL);
            if (canonicalPath != NULL) {
                strncpy(exePath,canonicalPath,len);
                free(canonicalPath);
            }
        }
    #elif __FreeBSD__
        char exePath[2048];
        int mib[4];  mib[0] = CTL_KERN;  mib[1] = KERN_PROC;  mib[2] = KERN_PROC_PATHNAME;  mib[3] = -1;
        size_t len = sizeof(exePath);
        if (sysctl(mib, 4, exePath, &len, NULL, 0) != 0)
            exePath[0] = '\0';
    #endif
	std::string filePath = std::string(exePath);
	int foundLastSlash = -1;
	for(int i=0;i<filePath.length();i++){
		if(filePath.substr(i, 1) == "/" || filePath.substr(i, 1) == "\\"){
			foundLastSlash = i;
		}
	}
	return(filePath.substr(0, foundLastSlash));
	
}
