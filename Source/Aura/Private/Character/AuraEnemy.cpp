// Copyright Flavio


#include "Character/AuraEnemy.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AAuraEnemy::HighlightActor()
{
	if (!HighlightMaterial) return;
	GetMesh()->SetOverlayMaterial(HighlightMaterial);
}

void AAuraEnemy::UnHighlight()
{
	GetMesh()->SetOverlayMaterial(nullptr);
}
