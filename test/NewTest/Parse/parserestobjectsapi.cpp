#include "parserestobjectsapi.h"

ParseRestObjectsApi::ParseRestObjectsApi(ParseConfiguration configuration) : ParseRestRequest(configuration){
    paths = std::make_unique<UrlPathBuilder>(
                configuration.getMountPath().append(paths->separator()).append("classes"));
}
