#ifndef __CTENCENTCLOUDAPI_INSTANCE_EXAMPLE_H__
#define __CTENCENTCLOUDAPI_INSTANCE_EXAMPLE_H__

#include "scenario.h"
#include <string>
#include <tencentcloud/cvm/v20170312/CvmClient.h>

class CTencentCloudApiInstanceExample: public CAbstractScenario
{
public:
    CTencentCloudApiInstanceExample() { _cvm_client = nullptr; };
    ~CTencentCloudApiInstanceExample() {};

    void Init();
    bool action();
    void destory();
    CAbstractScenario *create_copy() {
        return new CTencentCloudApiInstanceExample();
    }

public:
    TencentCloud::Cvm::V20170312::CvmClient *_cvm_client;
    TencentCloud::Cvm::V20170312::Model::DescribeInstancesRequest _req;
};

#endif
