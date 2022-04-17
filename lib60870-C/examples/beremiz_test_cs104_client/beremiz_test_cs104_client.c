#include "cs104_connection.h"
#include "hal_time.h"
#include "hal_thread.h"

#include <stdio.h>
#include <stdlib.h>

void printCP56Time(CP56Time2a time)
{
    printf("%02i:%02i:%02i %02i/%02i/%04i", CP56Time2a_getHour(time),
                             CP56Time2a_getMinute(time),
                             CP56Time2a_getSecond(time),
                             CP56Time2a_getDayOfMonth(time),
                             CP56Time2a_getMonth(time),
                             CP56Time2a_getYear(time) + 2000);
}

void printCP24Time(CP24Time2a time)
{
    printf("%02i:%02i:%02i", CP24Time2a_getMinute(time),
    						 CP24Time2a_getSecond(time),
    						 CP24Time2a_getMillisecond(time));
}

static void connectionHandler (void* parameter, CS104_Connection connection, CS104_ConnectionEvent event)
{
    switch (event) {
    case CS104_CONNECTION_OPENED:
        printf("Connection established\n");
        break;
    case CS104_CONNECTION_CLOSED:
        printf("Connection closed\n");
        break;
    case CS104_CONNECTION_STARTDT_CON_RECEIVED:
        printf("Received STARTDT_CON\n");
        break;
    case CS104_CONNECTION_STOPDT_CON_RECEIVED:
        printf("Received STOPDT_CON\n");
        break;
    }
}

static bool asduReceivedHandler (void* parameter, int address, CS101_ASDU asdu)
{

    //printf("Received asdu with type %d and COT %d\n", CS101_ASDU_getTypeID(asdu), CS101_ASDU_getCOT(asdu));
    if(CS101_ASDU_getCOT(asdu) == CS101_COT_PERIODIC) {
    	printf("ASDU Received:  ");
    	printf("CS101_COT_PERIODIC    ");
    	if(CS101_ASDU_getTypeID(asdu) == M_SP_NA_1) {
    		SinglePointInformation io = (SinglePointInformation) CS101_ASDU_getElement(asdu, 0);
    		printf("M_SP_NA_1    IOA: %i    value: %i\n",
    				InformationObject_getObjectAddress((InformationObject) io),
    				SinglePointInformation_getValue(io));
    		InformationObject_destroy((InformationObject)io);
    	}
    	if(CS101_ASDU_getTypeID(asdu) == M_DP_NA_1) {
    		DoublePointInformation io = (DoublePointInformation) CS101_ASDU_getElement(asdu, 0);
    		printf("M_DP_NA_1    IOA: %i    value: %i\n",
    				InformationObject_getObjectAddress((InformationObject) io),
    				DoublePointInformation_getValue(io));
    		InformationObject_destroy((InformationObject)io);
    	}
    	if(CS101_ASDU_getTypeID(asdu) == M_DP_TA_1) {
			DoublePointWithCP24Time2a io = (DoublePointWithCP24Time2a) CS101_ASDU_getElement(asdu, 0);
			printf("M_DP_TA_1    IOA: %i    value: %i    time: ",
					InformationObject_getObjectAddress((InformationObject) io),
					DoublePointInformation_getValue((DoublePointInformation)io));
			CP24Time2a time = DoublePointWithCP24Time2a_getTimestamp(io);
			printCP24Time(time);
			printf("\n");
			InformationObject_destroy((InformationObject)io);
    	}
    	if(CS101_ASDU_getTypeID(asdu) == M_BO_NA_1) {
            BitString32 io = (BitString32) CS101_ASDU_getElement(asdu, 0);
            printf("M_BO_NA_1    IOA: %i    value: %i\n",
                    InformationObject_getObjectAddress((InformationObject) io),
                    BitString32_getValue(io));
            InformationObject_destroy((InformationObject)io);
        }
    	if(CS101_ASDU_getTypeID(asdu) == M_ME_NA_1) {
    		MeasuredValueNormalized io = (MeasuredValueNormalized) CS101_ASDU_getElement(asdu, 0);
            printf("M_ME_NA_1    IOA: %i    value: %f\n",
                    InformationObject_getObjectAddress((InformationObject) io),
                    MeasuredValueNormalized_getValue(io));
            InformationObject_destroy((InformationObject)io);
        }
    	if(CS101_ASDU_getTypeID(asdu) == M_ME_NB_1) {
    		MeasuredValueScaled io = (MeasuredValueScaled) CS101_ASDU_getElement(asdu, 0);
            printf("M_ME_NB_1    IOA: %i    value: %i\n",
                    InformationObject_getObjectAddress((InformationObject) io),
                    MeasuredValueScaled_getValue(io));
            InformationObject_destroy((InformationObject)io);
        }
    	if(CS101_ASDU_getTypeID(asdu) == M_ME_NC_1) {
    		MeasuredValueShort io = (MeasuredValueShort) CS101_ASDU_getElement(asdu, 0);
            printf("M_ME_NC_1    IOA: %i    value: %f\n",
                    InformationObject_getObjectAddress((InformationObject) io),
                    MeasuredValueShort_getValue(io));
            InformationObject_destroy((InformationObject)io);
        }
    	if(CS101_ASDU_getTypeID(asdu) == M_ME_ND_1) {
    		MeasuredValueNormalizedWithoutQuality io = (MeasuredValueNormalizedWithoutQuality) CS101_ASDU_getElement(asdu, 0);
            printf("M_ME_ND_1    IOA: %i    value: %f\n",
                    InformationObject_getObjectAddress((InformationObject) io),
                    MeasuredValueNormalizedWithoutQuality_getValue(io));
            InformationObject_destroy((InformationObject)io);
        }
    	if(CS101_ASDU_getTypeID(asdu) == M_SP_TB_1) {
    		SinglePointWithCP56Time2a io = (SinglePointWithCP56Time2a) CS101_ASDU_getElement(asdu, 0);
            printf("M_SP_TB_1    IOA: %i    value: %i    time: ",
                    InformationObject_getObjectAddress((InformationObject) io),
                    SinglePointInformation_getValue((SinglePointInformation)io));
			CP56Time2a time = SinglePointWithCP56Time2a_getTimestamp(io);
			printCP56Time(time);
			printf("\n");
            InformationObject_destroy((InformationObject)io);
        }
    	if(CS101_ASDU_getTypeID(asdu) == M_DP_TB_1) {
			DoublePointWithCP56Time2a io = (DoublePointWithCP56Time2a) CS101_ASDU_getElement(asdu, 0);
			printf("M_DP_TB_1    IOA: %i    value: %i    time: ",
					InformationObject_getObjectAddress((InformationObject) io),
					DoublePointInformation_getValue((DoublePointInformation)io));
			CP56Time2a time = DoublePointWithCP56Time2a_getTimestamp(io);
			printCP56Time(time);
			printf("\n");
			InformationObject_destroy((InformationObject)io);
    	}
    	if(CS101_ASDU_getTypeID(asdu) == M_BO_TB_1) {
    		Bitstring32WithCP56Time2a io = (Bitstring32WithCP56Time2a) CS101_ASDU_getElement(asdu, 0);
            printf("M_BO_TB_1    IOA: %i    value: %i    time: ",
                    InformationObject_getObjectAddress((InformationObject) io),
                    BitString32_getValue((BitString32)io));
			CP56Time2a time = Bitstring32WithCP56Time2a_getTimestamp(io);
			printCP56Time(time);
			printf("\n");
            InformationObject_destroy((InformationObject)io);
        }
    	if(CS101_ASDU_getTypeID(asdu) == M_ME_TD_1) {
    		MeasuredValueNormalizedWithCP56Time2a io = (MeasuredValueNormalizedWithCP56Time2a) CS101_ASDU_getElement(asdu, 0);
            printf("M_ME_TD_1    IOA: %i    value: %f    time: ",
                    InformationObject_getObjectAddress((InformationObject) io),
                    MeasuredValueNormalized_getValue((MeasuredValueNormalized)io));
			CP56Time2a time = MeasuredValueNormalizedWithCP56Time2a_getTimestamp(io);
			printCP56Time(time);
			printf("\n");
            InformationObject_destroy((InformationObject)io);
        }
    	if(CS101_ASDU_getTypeID(asdu) == M_ME_TE_1) {
    		MeasuredValueScaledWithCP56Time2a io = (MeasuredValueScaledWithCP56Time2a) CS101_ASDU_getElement(asdu, 0);
            printf("M_ME_TE_1    IOA: %i    value: %i    time: ",
                    InformationObject_getObjectAddress((InformationObject) io),
                    MeasuredValueScaled_getValue((MeasuredValueScaled)io));
			CP56Time2a time = MeasuredValueScaledWithCP56Time2a_getTimestamp(io);
			printCP56Time(time);
			printf("\n");
            InformationObject_destroy((InformationObject)io);
        }
    	if(CS101_ASDU_getTypeID(asdu) == M_ME_TF_1) {
    		MeasuredValueShortWithCP56Time2a io = (MeasuredValueShortWithCP56Time2a) CS101_ASDU_getElement(asdu, 0);
            printf("M_ME_TF_1    IOA: %i    value: %f    time: ",
                    InformationObject_getObjectAddress((InformationObject) io),
                    MeasuredValueShort_getValue((MeasuredValueShort)io));
			CP56Time2a time = MeasuredValueShortWithCP56Time2a_getTimestamp(io);
			printCP56Time(time);
			printf("\n");
            InformationObject_destroy((InformationObject)io);
        }
    }
    return true;
}

int main(int argc, char** argv)
{

    const char* ip = "127.0.0.1";
	uint16_t port = IEC_60870_5_104_DEFAULT_PORT;


	//const char* localIp = NULL;
	//int localPort = -1;

	printf("Connecting to: %s:%i\n", ip, port);
	CS104_Connection con = CS104_Connection_create(ip, port);

	CS101_AppLayerParameters alParams = CS104_Connection_getAppLayerParameters(con);
	if(argc == 2)
		alParams->originatorAddress = atoi(argv[1]);
	else
		alParams->originatorAddress = 3;

	CS104_Connection_setConnectionHandler(con, connectionHandler, NULL);
	CS104_Connection_setASDUReceivedHandler(con, asduReceivedHandler, NULL);


	struct sCP56Time2a testTimestamp;
	CP56Time2a_createFromMsTimestamp(&testTimestamp, Hal_getTimeInMs());

	if (CS104_Connection_connect(con)) {
		printf("Connected!\n");

		CS104_Connection_sendStartDT(con);

		struct sCP56Time2a testTimestamp;
		CP56Time2a_createFromMsTimestamp(&testTimestamp, Hal_getTimeInMs());
		CS104_Connection_sendClockSyncCommand(con, 1, &testTimestamp);

		while(true) {
			Thread_sleep(2000);
	/*

			CS101_ASDU newAsdu = CS101_ASDU_create(alParams, false, CS101_COT_ACTIVATION, 0, 1, false, false);
			BitString32 io = (BitString32) BitString32_create(NULL, 0, 0);
			CS101_ASDU_addInformationObject(newAsdu, (InformationObject)io);
			CS101_ASDU_setTypeID(newAsdu, C_BO_NA_1);
			//InformationObject_destroy(io);
			CS104_Connection_sendASDU(con, newAsdu);
	*/
			//CS101_ASDU_destroy(newAsdu);


			//CS104_Connection_sendInterrogationCommand(con, CS101_COT_ACTIVATION, 1, IEC60870_QOI_STATION);
			//CS104_Connection_sendReadCommand(con, 1, 0);

		}

		//Thread_sleep(5000);
/*
		struct sCP56Time2a testTimestamp;
		CP56Time2a_createFromMsTimestamp(&testTimestamp, Hal_getTimeInMs());
		CS104_Connection_sendTestCommandWithTimestamp(con, 1, 0x4938, &testTimestamp);
*/
		Thread_sleep(1000);
	}
	else
		printf("Connect failed!\n");

	Thread_sleep(5000);

	CS104_Connection_destroy(con);


	return 0;
}
