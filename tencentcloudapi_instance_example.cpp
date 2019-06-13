#include <tencentcloud/core/TencentCloud.h>
#include <tencentcloud/core/profile/HttpProfile.h>
#include <tencentcloud/core/profile/ClientProfile.h>
#include <tencentcloud/core/Credential.h>
#include <tencentcloud/core/NetworkProxy.h>
#include <tencentcloud/core/AsyncCallerContext.h>
#include <tencentcloud/cvm/v20170312/CvmClient.h>
#include <tencentcloud/cvm/v20170312/model/DescribeInstancesRequest.h>
#include <tencentcloud/cvm/v20170312/model/DescribeInstancesResponse.h>
#include <tencentcloud/cvm/v20170312/model/Instance.h>

#include <iostream>
#include "tencentcloudapi_instance_example.h"

using namespace TencentCloud;
using namespace TencentCloud::Cvm::V20170312;
using namespace TencentCloud::Cvm::V20170312::Model;
using namespace std;

void CTencentCloudApiInstanceExample::Init()
{
    m_thread_num = 1;
    m_run_count = 10;
    m_name = "tencentcloudapi_example";

    //TencentCloud::InitAPI();
    string secretId = "xxxxxx";
    string secretKey = "xxxxxxx";
    Credential cred = Credential(secretId, secretKey);

    HttpProfile httpProfile = HttpProfile();
    httpProfile.SetEndpoint("cvm.ap-guangzhou.tencentcloudapi.com");
    httpProfile.SetReqTimeout(5);

    ClientProfile clientProfile = ClientProfile(httpProfile);

    DescribeInstancesRequest req = DescribeInstancesRequest();
    req.SetOffset(0);
    req.SetLimit(2);

    _cvm_client = new CvmClient(cred, "ap-guangzhou", clientProfile);
}

bool CTencentCloudApiInstanceExample::action()
{
    auto outcome = _cvm_client->DescribeInstances(_req);
    if (!outcome.IsSuccess())
    {
        cout << outcome.GetError().PrintAll() << endl;
        return false;
    }
    //DescribeInstancesResponse rsp = outcome.GetResult();
    //cout<<"RequestId="<<rsp.GetRequestId()<<endl;
    return true;
}

void CTencentCloudApiInstanceExample::destory()
{
    //TencentCloud::ShutdownAPI();
}

