#include "LMsg.h"
#include "LLog.h"
#include "LMsgS2S.h"
#include "LMsgCT.h"

LMsg::LMsg(int id)
:m_msgId(id), m_isMsgPack(false)
{

}

LMsg::~LMsg()
{

}

LBuffPtr LMsg::GetSendBuff()
{
	if(!m_send)
	{
		m_send.reset(new LBuff());
		if(preAllocSendMemorySize() > BUFF_SIZE)
		{
			m_send->Alloc(preAllocSendMemorySize());
		}

		if (m_isMsgPack)
		{
			msgpack::sbuffer buffer;
			msgpack::packer<msgpack::sbuffer> pac(&buffer);
			Write(pac); 

			MsgHeader header = {(unsigned short)(buffer.size()), 0, 0, 0};
			m_send->Write((char*)&header, sizeof(header));

			m_send->Write(buffer.data(), buffer.size());
		}
		else
		{
			LBuff tmpBuff;
			WriteMsgId(tmpBuff);
			Write(tmpBuff);

			MsgHeader header = {(unsigned short)(tmpBuff.Size()), 0, 0, 0};
			m_send->Write((char*)&header, sizeof(header));
			m_send->Write(tmpBuff.Data(), tmpBuff.Size());
		}
	}
	return m_send;
}

void LMsg::WriteMsgId(LBuff& buff)
{
	buff.Write(m_msgId);
}

//void LMsg::ReadMsgId(LBuff& buff)
//{
//	buff.Write(m_msgId);
//}

bool LMsg::Read(LBuff& buff)
{
	return true;
}

bool LMsg::Read(msgpack::object& pack)
{
	return true;
}

bool LMsg::Write(LBuff& buff)
{
	return true;
}

bool LMsg::Write(msgpack::packer<msgpack::sbuffer>& pack)
{
	return true;
}

LMsg* LMsg::Clone()
{
	return NULL;
}

Lint LMsg::preAllocSendMemorySize()
{
	return BUFF_SIZE;
}

//////////////////////////////////////////////////////////////////////////
bool LMsgFactory::Init()
{
	Final();

	RegestMsg(new LMsgIn());
	RegestMsg(new LMsgKick());
	RegestMsg(new LMsgHttp());

	RegestMsg(new LMsgC2SMsg());
	RegestMsg(new LMsgS2CMsg());

	RegestMsg(new LMsgC2SHeart());
	RegestMsg(new LMsgS2CHeart());
	RegestMsg(new LMsgC2SNotice());
	RegestMsg(new LMsgS2CNotice());

	RegestMsg(new LMsgC2SReLogin());
	RegestMsg(new LMsgC2SLogin());
	RegestMsg(new LMsgS2CLogin());
	RegestMsg(new LMsgL2CeSaveCardInfo());
	RegestMsg(new LMsgL2CeUserServerLogin());
	RegestMsg(new LMsgL2CeUserServerLogout());

	RegestMsg(new LMsgS2CItemInfo());
	RegestMsg(new LMsgS2CHorseInfo());

	RegestMsg(new LMsgS2CIntoDesk());
	RegestMsg(new LMsgS2CDeskAddUser());
	RegestMsg(new LMsgS2CDeskDelUser());
	RegestMsg(new LMsgC2SSelectResetDesk());
	RegestMsg(new LMsgS2CResetDesk());
	RegestMsg(new LMsgC2SResetDesk());

	RegestMsg(new LMsgS2CDeskState());

	RegestMsg(new LMsgC2SUserReady());
	RegestMsg(new LMsgS2CUserReady());

	RegestMsg(new LMsgS2CPlayStart());
	RegestMsg(new LMsgS2COutCard());
	RegestMsg(new LMsgC2SUserPlay());
	RegestMsg(new LMsgS2CUserPlay());
	RegestMsg(new LMsgS2CThink());
	RegestMsg(new LMsgC2SUserOper());
	RegestMsg(new LMsgS2CUserOper());
	RegestMsg(new LMsgS2CGameOver());
	RegestMsg(new LMsgS2CCard());
	RegestMsg(new LMsgS2COnlyOneCard());

	RegestMsg(new LMsgS2CUserStartHu());
	RegestMsg(new LMsgC2SUserStartHuSelect());
	RegestMsg(new LMsgS2CUserStartHuSelect());

	RegestMsg(new LMsgS2CUserGangCard());
	RegestMsg(new LMsgS2CUserEndCardSelect());
	RegestMsg(new LMsgC2SUserEndCardSelect());
	RegestMsg(new LMsgS2CUserEndCardGet());

	RegestMsg(new LMsgC2SUserOutRoom());
	RegestMsg(new LMsgS2CUserOutRoom());

	RegestMsg(new LMsgC2SLeaveDesk());
	RegestMsg(new LMsgS2CLeaveDesk());

	RegestMsg(new LMsgC2SUserSpeak());
	RegestMsg(new LMsgS2CUserSpeak());

	RegestMsg(new LMsgC2SCreateDesk());
	RegestMsg(new LMsgS2CCreateDeskRet());

	RegestMsg(new LMsgC2SAddDesk());
	RegestMsg(new LMsgS2CAddDeskRet());

	
	RegestMsg(new LMsgS2CVipEnd());
	RegestMsg(new LMsgC2SVipLog());
	RegestMsg(new LMsgS2CVipLog());
	RegestMsg(new LMsgC2SVideo());
	RegestMsg(new LMsgS2CVideo());

	RegestMsg(new LMsgC2SOneVipLog());
	RegestMsg(new LMsgS2COneVipLog());

	//RegestMsg(new LMsgS2CUserChargeDiamond());
	RegestMsg(new LMsgS2CUserPurchase());

	RegestMsg(new LMsgS2CPlayerType());

	RegestMsg(new LMsgL2CeLogin());
	RegestMsg(new LMsgL2CeGateInfo());
	RegestMsg(new LMsgCe2LUserLogin());
	RegestMsg(new LMsgCe2LUserIdInfo());

	RegestMsg(new LMsgLMG2CeSaveUserPlayCount());

	RegestMsg(new LMsgG2LLogin());
	RegestMsg(new LMsgG2LUserMsg());
	RegestMsg(new LMsgL2GUserMsg());
	RegestMsg(new LMsgL2CeSaveUser());
	RegestMsg(new LMsgL2CeSaveLogItem());

	RegestMsg(new LMsgCe2LGMCharge());
	RegestMsg(new LMsgCe2LGMHorse());
	RegestMsg(new LMsgCe2LGMBuyInfo());
	RegestMsg(new LMsgCe2LGMHide());
	RegestMsg(new LMsgCe2LGMModifyPlayerType());
	RegestMsg(new LMsgCe2LGMChargeDiamond());
	RegestMsg(new LMsgCe2LGMPurchase());
	RegestMsg(new LMsgLMG2CeCardExchange());
	RegestMsg(new LMsgLMG2CeGoldChange());

	RegestMsg(new LMsgG2LUserOutMsg());
	RegestMsg(new LMsgL2GUserOutMsg());

	//抽奖活动;
	RegestMsg(new LMsgL2LDBReqActive());
	RegestMsg(new LMsgLDB2LActiveInfo());
	RegestMsg(new LMsgL2LDBSyncDraw());
	RegestMsg(new LMsgL2LDBSyncPhone());
	RegestMsg(new LMsgS2CActiveInfo());
	RegestMsg(new LMsgC2SRequestDraw());
	RegestMsg(new LMsgS2CFinishDraw());
	RegestMsg(new LMsgC2SWritePhone());
	RegestMsg(new LMsgS2CWritePhone());
	RegestMsg(new LMsgC2SActiveLog());
	RegestMsg(new LMsgS2CDrawInfo());
	RegestMsg(new LMsgS2CActiveOpen());
	RegestMsg(new LMsgC2SActiveInfoRequest());

	RegestMsg(new LMsgC2SWealthChange());
	RegestMsg(new LMsgS2CWealthChangeResult());

	//2016年十一活动
	RegestMsg(new LMsgC2SReqSignCollect());	//签到,集字;
	RegestMsg(new LMsgS2CResSign());	//签到结果;
	RegestMsg(new LMsgS2CResCollect());	//收集字符结果;

	RegestMsg(new LMsgC2SReqSignCollectWinState());	//请求签到状态;
	RegestMsg(new LMsgS2CResSignState());	//回复签到状态;
	RegestMsg(new LMsgS2CResCollectState());	//回复收集字符状态;
	RegestMsg(new LMsgS2CResWinState());	//回复中奖状态;

	RegestMsg(new LMsgS2CGoldChange());	//金币变化情况; 
	RegestMsg(new LMsgL2LMGGoldChange()); //金币变化logic通知LM;
	RegestMsg(new LMsgC2SAskGoldDeskState()); //金币变化logic通知LM;
	RegestMsg(new LMsgS2CGoldDeskState()); //金币变化logic通知LM;

	RegestMsg(new LMsgL2LDBReqSignCollectWin());	//请求load十一活动;
	RegestMsg(new LMsgLDB2LResSignCollectWin());	//返回十一活动;
	
	RegestMsg(new LMsgL2LDBSaveSignCollectWin());	//请求保存数据库;
	RegestMsg(new LMsgL2LMGAddUserBashu());		//统计把数;
	//end 十一活动
	
	RegestMsg(new LMsgL2LdbLogin());
	RegestMsg(new LMsgL2LDBSaveLogItem());
	RegestMsg(new LMsgL2LDBSaveVideo());
	RegestMsg(new LMsgL2LBDReqVipLog());
	RegestMsg(new LMsgLBD2LReqVipLog());
	RegestMsg(new LMsgL2LDBReqVideo());
	RegestMsg(new LMsgLDB2LReqVideo());

	RegestMsg(new LMsgL2CeUerReLogin());
	RegestMsg(new LMsgCe2LUserReLogin());
			
	RegestMsg(new LMsgLDB2LLogInfo());

	RegestMsg(new LMsgC2SShareVideo());
	RegestMsg(new LMsgS2CShareVideo());

	RegestMsg(new LMsgS2CAskDiZhu());
	RegestMsg(new LMsgS2CAnsDiZhu());
	RegestMsg(new LMsgS2CWhoIsDiZhu());
	RegestMsg(new LMsgC2SQiangDiZhu());
	RegestMsg(new LMsgS2CQDZQuery_Sichuan());
	RegestMsg(new LMsgC2SQdzOper_Sichuan());
	RegestMsg(new LMsgS2CQdzOper_Sichuan());
	
	RegestMsg(new LMsgC2SReqShareVideo());
	RegestMsg(new LMsgS2CRetShareVideoId());
	RegestMsg(new LMsgL2LDBGGetShareVideoId());
	RegestMsg(new LMsgL2LDBGetShareVideo());
	RegestMsg(new LMsgLDB2LRetShareVideoId());
	RegestMsg(new LMsgLDB2LRetShareVideo());
	RegestMsg(new LMsgL2LDBSaveShareVideoId());
	RegestMsg(new LMsgC2SGetShareVideo());
	RegestMsg(new LMsgL2LDBGetSsharedVideo());

	RegestMsg(new LMsgLMG2GateLogicInfo());
	RegestMsg(new LMsgL2LMGLogin());
	RegestMsg(new LMsgLMG2GHorseInfo());
	RegestMsg(new LMsgLMG2LLogin());
	RegestMsg(new LMsgL2LMGModifyUserState());
	RegestMsg(new LMsgL2GModifyUserState());
	RegestMsg(new LMsgLMG2LCreateDesk());
	RegestMsg(new LMsgLMG2LIntoGoldDesk());
	RegestMsg(new LMsgLMG2LAddToDesk());
	RegestMsg(new LMsgL2LMGModifyCard());
	RegestMsg(new LMsgL2LMGModifyPlayCount());
	RegestMsg(new LMsgG2LMGLogin());
	RegestMsg(new LMsgL2LMGRecyleDeskID());
	RegestMsg(new LMsgL2LMGRecyleGoldDeskPlace());
	RegestMsg(new LMsgL2LMGUseGoldDeskPlace());
	RegestMsg(new LMsgLMG2LdbLogin());
	RegestMsg(new LMsgG2LHEARTBEAT());
	RegestMsg(new LMsgL2GHEARTBEAT_BACK());
	RegestMsg(new LMsgG2LMGHEARTBEAT());
	RegestMsg(new LMsgLMG2GHEARTBEAT_BACK());
	RegestMsg(new LMsgL2LMGHEARTBEAT());
	RegestMsg(new LMsgLMG2LHEARTBEAT_BACK());
	RegestMsg(new LMsgL2LDBHEARTBEAT());
	RegestMsg(new LMsgLDB2LHEARTBEAT_BACK());
	RegestMsg(new LMsgLMG2LDBHEARTBEAT());
	RegestMsg(new LMsgLDB2LMGHEARTBEAT_BACK());
	RegestMsg(new LMsgLMG2CEHEARTBEAT());
	RegestMsg(new LMsgCE2LMGHEARTBEAT_BACK());

	RegestMsg(new LMsgL2LDBReqOneVipLog());
	RegestMsg(new LMsgLBD2LReqOneVipLog());
	//RegestMsg(new LMsgC2SCouponsExchange());
	RegestMsg(new LMsgS2CCouponsExchange());
	RegestMsg(new LMsgC2SCouponsExchangeRecord());
	RegestMsg(new LMsgS2CCouponsExchangeRecord());
	RegestMsg(new LMsgCE2LMGUserGiftInfo());
	RegestMsg(new LMsgLMG2CEUserCouponsExchangeRecord());
	RegestMsg(new LMsgC2SGiftExchange());
	RegestMsg(new LMsgCE2LMGUserCouponsExchangeRecord());
	RegestMsg(new LMsgLMG2CEUserCouponsExchangeInfo());
	RegestMsg(new LMsgS2CGiftExchange());

	//玩家任务和推荐;
	RegestMsg(new LMsgC2SGetTask);
	RegestMsg(new LMsgS2CTaskList);
	RegestMsg(new LMsgC2SRecvTaskReward);
	RegestMsg(new LMsgS2CRecvTaskReward);
	RegestMsg(new LMsgC2SGetUserInfo);
	RegestMsg(new LMsgS2CUserInfo);
	RegestMsg(new LMsgC2SGetInvitingInfo);
	RegestMsg(new LMsgS2CInvitingInfo);
	RegestMsg(new LMsgC2SBindInviter);
	RegestMsg(new LMsgS2CBindInviter);
	RegestMsg(new LMsgC2SUserShared);
	RegestMsg(new LMsgL2LDBExecSql);
	RegestMsg(new LMsgLMG2LDBReqTaskProgress);
	RegestMsg(new LMsgLDB2LMGTaskProgress);
	RegestMsg(new LMsgLMG2LDBReqBindingRelationships);
	RegestMsg(new LMsgLDB2LMGBindingRelationships);
	RegestMsg(new LMsgLMG2LDBInsertTaskProgress);
	RegestMsg(new LMsgLDB2LMGInsertTaskProgress);
	RegestMsg(new LMsgL2LMGUserCircleIncreased);
	RegestMsg(new LMsgLMG2LDBReqActiveGiftStock);
	RegestMsg(new LMsgLDB2LMGActiveGiftStock);
	RegestMsg(new LMsgLMG2LDBReqLuckyDrawNum);
	RegestMsg(new LMsgLDB2LMGLuckyDrawNum);
	RegestMsg(new LMsgC2SReqLuckyDrawNum);
	RegestMsg(new LMsgS2CLuckyDrawNum);
	RegestMsg(new LMsgLMG2CeOfflineUserCardChanged);
	RegestMsg(new LMsgLMG2LDBInsertBindingRelationship);
	RegestMsg(new LMsgLDB2LMGInsertBindingRelationship);

	RegestMsg(new LMsgLGCEUserMsgWrapper);
	RegestMsg(new LMsgLG2CEHeartBeat);

	RegestMsg(new LMsgS2SKeepAlive);
	RegestMsg(new LMsgS2SKeepAliveAck);

	//MaYouQuan begin
	// 工会 [2017-7-10 willing]
	RegestMsg(new LMsgTS2LMG_Login());
	RegestMsg(new LMsgTS2LMG_Heartbeat());
	RegestMsg(new LMsgLMG2TS_Heartbeat());
	RegestMsg(new LMsgTS2LDB_Login());
	RegestMsg(new LMsgTS2LDB_Heartbeat());
	RegestMsg(new LMsgLDB2TS_Heartbeat());
	RegestMsg(new LMsgL2TS_Login());
	RegestMsg(new LMsgL2TS_Heartbeat());
	RegestMsg(new LMsgTS2L_Heartbeat());
	RegestMsg(new LMsgLMG2L_TeamServer());
	RegestMsg(new LMsgLMG2G_TeamServer());
	RegestMsg(new LMsgG2TS_Heartbeat());
	RegestMsg(new LMsgTS2G_Heartbeat());
	RegestMsg(new LMsgG2TS_Login());
	RegestMsg(new LMsgLMG2TS_LogicGateLogout());

	RegestMsg(new LMsgLMG2LModifyRoomCard());
	RegestMsg(new LMsgS2CDeskUserScoreCharge());
	RegestMsg(new LMsgS2CBrocastUserNoGold());

	RegestMsg(new LMsgC2SReqExchageGold());
	RegestMsg(new LMsgS2CReqExchageGold());
	RegestMsg(new LMsgC2SReqExchageGoldLog());
	RegestMsg(new LMsgS2CExchageGoldOptLog());
	RegestMsg(new LMsgTS2LMG_ReqExchageGold());
	RegestMsg(new LMsgLMG2TS_ReqExchageGold());
	RegestMsg(new LMsgS2CExchageGoldOptNotice());
	RegestMsg(new LMsgC2SInviteInRoom());
	RegestMsg(new LMsgS2CInviteInRoom());

	RegestMsg(new LMsgC2SQuerTeam());
	RegestMsg(new LMsgG2TUserMsg());
	RegestMsg(new LMsgT2GUserMsg());
	RegestMsg(new LMsgLMG2TS_UserLogin());
	RegestMsg(new LMsgLMG2TS_UserLogout());
	RegestMsg(new LMsgS2CQueryTeamInfo());
	RegestMsg(new LMsgC2SReqJoin());
	RegestMsg(new LMsgS2CJoinRst());
	RegestMsg(new LMsgS2CNoticeEvent());
	RegestMsg(new LMsgC2SReqTeamList());
	RegestMsg(new LMsgS2CTeamList());
	RegestMsg(new LMsgC2SGetTeamInfo());
	RegestMsg(new LMsgS2CTeamInfo());
	RegestMsg(new LMsgC2SGetTeamMemberList());
	RegestMsg(new LMsgS2CMemberList());
	RegestMsg(new LMsgC2SCancelJoin());
	RegestMsg(new LMsgS2CCancelJoin());
	RegestMsg(new LMsgC2SLeaveTeam());
	RegestMsg(new LMsgS2CLeaveTeamRst());
	RegestMsg(new LMsgLMG2TS_CreateDesk());
	RegestMsg(new LMsgC2SCreateTeamDeskError());
	RegestMsg(new LMsgTS2LMG_CreateDesk());
	RegestMsg(new LMsgS2CTeamInfoChange());
	RegestMsg(new LMsgLMG2TS_GiveBackCard());
	RegestMsg(new LMsgL2TS_DelCard());
	RegestMsg(new LMsgL2TS_VideoLog());
	RegestMsg(new LMsgL2TS_AddDesk());
	RegestMsg(new LMsgTS2L_AddDeskRet());
	RegestMsg(new LMsgC2SGetVideoLog());
	RegestMsg(new LMsgLS2TS_GameState());
	RegestMsg(new LMsgS2CMemberInfoChange());
	RegestMsg(new LMsgTS2LMG_GetUserInfo());
	RegestMsg(new LMsgLMG2TS_UserInfo());
	RegestMsg(new LMsgTS2LMG_TeamVideoLog());
	RegestMsg(new LMsgL2TS_NewTeamDesk());
	RegestMsg(new LMsgS2CNewTeamDesk());
	RegestMsg(new LMsgL2TS_TeamDeskUserChg());
	RegestMsg(new LMsgL2TS_DelTeamDesk());
	RegestMsg(new LMsgS2CDelTeamDesk());
	RegestMsg(new LMsgC2SGetAllTeamDesk());
	RegestMsg(new LMsgS2CAllTeamDesk());
	RegestMsg(new LMsgC2SSubscribeTeamDesk());
	RegestMsg(new LMsgTS2LMG_QueryIsOnLine());
	RegestMsg(new LMsgS2CTeamDeskUserChg());
	RegestMsg(new LMsgLMG2TS_RecycleDeskId());
	RegestMsg(new LMsgC2SGetTeamOptLog());
	RegestMsg(new LMsgS2CMemTeamOptLog());
	RegestMsg(new LMsgC2SGetRangeVideoLog());
	RegestMsg(new LMsgLMG2TS_AddDesk());
	RegestMsg(new LMsgTS2LMG_AddDesk());
	RegestMsg(new LMsgC2SCreatePlayConfig());
	RegestMsg(new LMsgS2CFastPlayRet());
	RegestMsg(new LMsgC2SFastPlay());
	RegestMsg(new LMsgTS2LMG_ReqDeskId());
	RegestMsg(new LMsgLMG2TS_ReqDeskRet());
	RegestMsg(new LMsgC2SOptMember());
	RegestMsg(new LMsgS2COptMemRet());
	RegestMsg(new LMsgS2CTeamPlayConfig());
	RegestMsg(new LMsgC2SOptTeamInfo());
	RegestMsg(new LMsgC2SAdminInviteOther());
	RegestMsg(new LMsgS2CAdminInviteOtherRet());
	RegestMsg(new LMsgTS2LMG_UserLogin());
	RegestMsg(new LMsgTS2LMG_UserInLogic());

	RegestMsg(new LMsgMa2LM_UserMatchInfo());

	//移植广西分享好友获取房卡活动：
	RegestMsg(new LMsgC2SRequest_Share_Card);

	//////////////////////长沙麻将 begin///////////////////////

	RegestMsg(new LMsgS2CPiaoSelect());
	RegestMsg(new LMsgC2SPiaoSelect());

	RegestMsg(new LMsgC2SCancelManaged());
	RegestMsg(new LMsgS2CAttachManaged);

	RegestMsg(new LMsgL2LMGSportResult);
	RegestMsg(new LMsgLMG2CESportResetDesk);
	RegestMsg(new LMsgLMG2LMatchAddDesk);
	RegestMsg(new LMsgLMG2LogicMatchInfo);

	RegestMsg(new LMsgL2MLogin);
	RegestMsg(new LMsgS2CUserGangThinkCard());
	RegestMsg(new LMsgL2LMGUserCompleteGame);

	RegestMsg(new LMsgS2CSportTips);

	RegestMsg(new LMsgS2CZhaBirdShow());
	RegestMsg(new LMsgS2CWangBa());
	RegestMsg(new LMsgS2CUserOperTing());
	RegestMsg(new LMsgS2CCanTing);

	//////////////////////长沙麻将 end///////////////////////

	/////////////////////广东麻将////////////////////////////
	RegestMsg(new LMsgC2SInteraction);
	RegestMsg(new LMsgS2CInteraction);
	RegestMsg(new LMsgC2S_TuoGuan());
	RegestMsg(new LMsgS2C_TuoGuanInfo());
	RegestMsg(new LMsgC2SSignInInfoReq());
	RegestMsg(new LMsgS2CSignInInfoRes());
	RegestMsg(new LMsgC2SSignInReq());
	RegestMsg(new LMsgS2CSignInRes());

	RegestMsg(new LMsg_Match2L_CreateMatchDesk());
	RegestMsg(new LMsg_Match2L_ContralMatchDesk());
	RegestMsg(new LMsgLM2Gate2Logic_MatchServerInfo());

	RegestMsg(new LMsg_L2Match_Ret_ContralMatchDesk());
	RegestMsg(new LMsgS2C_MatchInfoText());

	RegestMsg(new LMsgL2Match_DeskCircleOverGoldInfo());
	RegestMsg(new LMsgL2LMGReportHorseInfo);
	RegestMsg(new LMsgS2CGhostCard());
	RegestMsg(new LMsgS2CGengZhuangSucc);

	/////////////////////广东麻将 end////////////////////////////
	return true;
}

bool LMsgFactory::Final()
{
	std::map<int,LMsg*>::iterator it = m_msgMap.begin();
	for(;it != m_msgMap.end();++it)
	{
		delete it->second;
	}
	return true;
}

void LMsgFactory::RegestMsg(LMsg* pMsg)
{
	std::map<int,LMsg*>::iterator it = m_msgMap.find(pMsg->m_msgId);
	if(it != m_msgMap.end())
	{
		LLOG_INFO("LMsgFactory::RegestMsg msg exiset msgId:%d",pMsg->m_msgId);
	}
	else
	{
		m_msgMap[pMsg->m_msgId] = pMsg;
	}
}

LMsg* LMsgFactory::CreateMsg(int msgId)
{
	std::map<int,LMsg*>::iterator it = m_msgMap.find(msgId);
	if(it == m_msgMap.end())
	{
		//LLOG_INFO("LMsgFactory::CreateMsg msg not exiset msgId:%d",msgId);
		return NULL;
	}
	else
	{
		return it->second->Clone();
	}
}
