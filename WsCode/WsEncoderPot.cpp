//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : WsEncoderPot.cpp
//  @ Date : 1/22/2011
//  @ Author : 
//
//


#include "WsEncoderPot.h"
#include "WsEncoder.h"
#include "WPILib.h"

WsEncoderPot::WsEncoderPot(UINT32 encoder_a,
                           UINT32 encoder_b,
                           UINT32 bottom_sw,
                           UINT32 top_sw)
{
    ap_encoder = new WsEncoder(encoder_a, encoder_b);
    ap_bot_sw = new DigitalInput(bottom_sw);
    ap_top_sw = new DigitalInput(top_sw);
    a_initialized = false;
    ap_encoder->Reset();
    ap_encoder->Start();
}

WsEncoderPot::~WsEncoderPot() {
    delete ap_encoder;
    ap_encoder = NULL;

    delete ap_bot_sw;
    ap_bot_sw = NULL;

    delete ap_top_sw;
    ap_top_sw = NULL;
}



INT32 WsEncoderPot::getValue() {

    if(isAtBottom())
    {
        ap_encoder->Reset();
        a_initialized = true;
    }

    return ap_encoder->Get();
}

bool WsEncoderPot::isInitialized() {
    return a_initialized;
}
bool WsEncoderPot::isAtTop() {
    return (ap_top_sw->Get() == SW_TOP_PRESSED);
}

bool WsEncoderPot::isAtBottom() {
    return (ap_bot_sw->Get() == SW_BOT_PRESSED);
}


