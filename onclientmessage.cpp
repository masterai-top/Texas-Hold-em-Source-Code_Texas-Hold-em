#include "head.pb.h"
#include "ddz.pb.h"
#include "gameroot.h"
#include "utils/tarslog.h"
#include "common/macros.h"
#include "message/onclientmessage.h"
#include "logic/clientlogic/head.h"

namespace game
{
    namespace message
    {
        void onClientMessage(long uid, int eMSG, const vector<char> &vecMsgData, GameRoot *root)
        {
            using namespace logic;

            try
            {
                switch(static_cast<unsigned char>(eMSG))
                {
                //下注请求及应答
                case XGameDDZProto::DDZ_msg2csDecision_E:
                {
                    clientlogic::Decision(uid, vecMsgData, root);
                }
                break;
                case XGameDDZProto::DDZ_msg2csGameStation_E:
                {
                    clientlogic::GameStation(uid, vecMsgData, root);
                }
                break;
                case XGameDDZProto::DDZ_msg2csReady_E:
                {
                    clientlogic::OnReady(uid, vecMsgData, root);
                }
                break;
                case XGameDDZProto::DDZ_msg2csTuoGuan_E:
                {
                    clientlogic::TuoGuan(uid, vecMsgData, root);
                }
                break;
                //
                default:
                {
                    LOG_ERROR("undefined network message from remote user, uid : " << uid << ", eMSG: " << eMSG);
                }
                break;
                }
            }
            catch (const TarsDecodeException &e)
            {
                ERROR(string("catch tars decode exception : ") + e.what());
            }
            catch (const TarsEncodeException &e)
            {
                ERROR(string("catch tars encode exception : ") + e.what());
            }
            catch (const TarsProtoException &e)
            {
                ERROR(string("catch proto exception : ") + e.what());
            }
            catch (const TC_Exception &e)
            {
                ERROR(string("catch tc exception : ") + e.what());
            }
            catch (const std::exception &e)
            {
                ERROR(string("catch std exception : ") + e.what());
            }
            catch (...)
            {
                ERROR("catch unknown exception.");
            }
        }
    };
};


