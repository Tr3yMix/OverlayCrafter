
#include "JarReader.h"

#include <cstdint>

#include "Logger.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "mz_strm.h"
#include "mz.h"
#include "mz_zip.h"
#include "mz_zip_rw.h"


void JarReader::listJarContents(const std::string &jarPath) {

    void* handle = mz_zip_reader_create();

    if(mz_zip_reader_open_file(handle, jarPath.c_str()) != MZ_OK) {
        log(Logger::LogType::Error, "Failed to open JAR file");
        mz_zip_reader_delete(&handle);
        return;
    }

    mz_zip_file* file_info = nullptr;
    int32_t entry_count = 0;
    while(mz_zip_reader_goto_next_entry(handle) == MZ_OK) {
        if(mz_zip_reader_entry_get_info(handle, &file_info) == MZ_OK) {
            if(std::string entryName = file_info->filename; entryName.find("textures/block/") != std::string::npos && entryName.ends_with(".png")) {
                log(Logger::LogType::Info, "Found block texture: ", entryName);
                ++entry_count;
            }
        }
    }

    logf(Logger::LogType::Info, "Found {} textures", entry_count);

    mz_zip_reader_close(handle);
    mz_zip_reader_delete(&handle);

}
