// Copyright Flavio


#include "Player/AuraPlayerState.h"

AAuraPlayerState::AAuraPlayerState()
{
	/*
	 * usually without GAS the update from server to client for PLayerState could be lower (each half second), 
	 * but with GAS we need faster
	 */
	SetNetUpdateFrequency(100.f);
}
