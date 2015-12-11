switch ( weaponNum ) {
	case WP_GAUNTLET:
		MAKERGB( weaponInfo->flashDlightColor, 0.6f, 0.6f, 1.0f );
		weaponInfo->firingSound = trap_S_RegisterSound( "sound/weapons/melee/fstrun.wav", qfalse );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/melee/fstatck.wav", qfalse );
		break;

	case WP_LIGHTNING:
		MAKERGB( weaponInfo->flashDlightColor, 0.6f, 0.6f, 1.0f );
		weaponInfo->readySound = trap_S_RegisterSound( "sound/weapons/melee/fsthum.wav", qfalse );
		weaponInfo->firingSound = trap_S_RegisterSound( "sound/weapons/lightning/lg_hum.wav", qfalse );

		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/lightning/lg_fire.wav", qfalse );
		cgs.media.lightningShader = trap_R_RegisterShader( "lightningBoltNew");
		cgs.media.lightningExplosionModel = trap_R_RegisterModel( "models/weaphits/crackle.md3" );
		cgs.media.sfx_lghit1 = trap_S_RegisterSound( "sound/weapons/lightning/lg_hit.wav", qfalse );
		cgs.media.sfx_lghit2 = trap_S_RegisterSound( "sound/weapons/lightning/lg_hit2.wav", qfalse );
		cgs.media.sfx_lghit3 = trap_S_RegisterSound( "sound/weapons/lightning/lg_hit3.wav", qfalse );

		break;

	case WP_GRAPPLING_HOOK:
		MAKERGB( weaponInfo->flashDlightColor, 0.6f, 0.6f, 1.0f );
		weaponInfo->missileModel = trap_R_RegisterModel( "models/ammo/rocket/rocket.md3" );
		weaponInfo->missileTrailFunc = CG_GrappleTrail;
		weaponInfo->missileDlight = 200;
		MAKERGB( weaponInfo->missileDlightColor, 1, 0.75f, 0 );
		weaponInfo->readySound = trap_S_RegisterSound( "sound/weapons/melee/fsthum.wav", qfalse );
		weaponInfo->firingSound = trap_S_RegisterSound( "sound/weapons/melee/fstrun.wav", qfalse );
		cgs.media.lightningShader = trap_R_RegisterShader( "lightningBoltNew");
		break;

#ifdef MISSIONPACK
	case WP_CHAINGUN:
		weaponInfo->firingSound = trap_S_RegisterSound( "sound/weapons/vulcan/wvulfire.wav", qfalse );
		MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/vulcan/vulcanf1b.wav", qfalse );
		weaponInfo->flashSound[1] = trap_S_RegisterSound( "sound/weapons/vulcan/vulcanf2b.wav", qfalse );
		weaponInfo->flashSound[2] = trap_S_RegisterSound( "sound/weapons/vulcan/vulcanf3b.wav", qfalse );
		weaponInfo->flashSound[3] = trap_S_RegisterSound( "sound/weapons/vulcan/vulcanf4b.wav", qfalse );
		weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
		cgs.media.bulletExplosionShader = trap_R_RegisterShader( "bulletExplosion" );
		break;
#endif

	case WP_MACHINEGUN:
		MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/machinegun/machgf1b.wav", qfalse );
		weaponInfo->flashSound[1] = trap_S_RegisterSound( "sound/weapons/machinegun/machgf2b.wav", qfalse );
		weaponInfo->flashSound[2] = trap_S_RegisterSound( "sound/weapons/machinegun/machgf3b.wav", qfalse );
		weaponInfo->flashSound[3] = trap_S_RegisterSound( "sound/weapons/machinegun/machgf4b.wav", qfalse );
		weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
		cgs.media.bulletExplosionShader = trap_R_RegisterShader( "bulletExplosion" );
		break;

	case WP_SHOTGUN:
		MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/shotgun/sshotf1b.wav", qfalse );
		weaponInfo->ejectBrassFunc = CG_ShotgunEjectBrass;
		break;

	case WP_ROCKET_LAUNCHER:
		weaponInfo->missileModel = trap_R_RegisterModel( "models/ammo/rocket/rocket.md3" );
		weaponInfo->missileSound = trap_S_RegisterSound( "sound/weapons/rocket/rockfly.wav", qfalse );
		weaponInfo->missileTrailFunc = CG_RocketTrail;
		weaponInfo->missileDlight = 200;
		weaponInfo->wiTrailTime = 2000;
		weaponInfo->trailRadius = 64;
		
		MAKERGB( weaponInfo->missileDlightColor, 1, 0.75f, 0 );
		MAKERGB( weaponInfo->flashDlightColor, 1, 0.75f, 0 );

		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/rocket/rocklf1a.wav", qfalse );
		cgs.media.rocketExplosionShader = trap_R_RegisterShader( "rocketExplosion" );
		break;

#ifdef MISSIONPACK
	case WP_PROX_LAUNCHER:
		weaponInfo->missileModel = trap_R_RegisterModel( "models/weaphits/proxmine.md3" );
		weaponInfo->missileTrailFunc = CG_GrenadeTrail;
		weaponInfo->wiTrailTime = 700;
		weaponInfo->trailRadius = 32;
		MAKERGB( weaponInfo->flashDlightColor, 1, 0.70f, 0 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/proxmine/wstbfire.wav", qfalse );
		cgs.media.grenadeExplosionShader = trap_R_RegisterShader( "grenadeExplosion" );
		break;
#endif

	case WP_GRENADE_LAUNCHER:
		weaponInfo->missileModel = trap_R_RegisterModel( "models/ammo/grenade1.md3" );
		weaponInfo->missileTrailFunc = CG_GrenadeTrail;
		weaponInfo->wiTrailTime = 700;
		weaponInfo->trailRadius = 32;
		MAKERGB( weaponInfo->flashDlightColor, 1, 0.70f, 0 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/grenade/grenlf1a.wav", qfalse );
		cgs.media.grenadeExplosionShader = trap_R_RegisterShader( "grenadeExplosion" );
		break;

#ifdef MISSIONPACK
	case WP_NAILGUN:
		weaponInfo->ejectBrassFunc = CG_NailgunEjectBrass;
		weaponInfo->missileTrailFunc = CG_NailTrail;
//		weaponInfo->missileSound = trap_S_RegisterSound( "sound/weapons/nailgun/wnalflit.wav", qfalse );
		weaponInfo->trailRadius = 16;
		weaponInfo->wiTrailTime = 250;
		weaponInfo->missileModel = trap_R_RegisterModel( "models/weaphits/nail.md3" );
		MAKERGB( weaponInfo->flashDlightColor, 1, 0.75f, 0 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/nailgun/wnalfire.wav", qfalse );
		break;
#endif

	case WP_PLASMAGUN:
//		weaponInfo->missileModel = cgs.media.invulnerabilityPowerupModel;
		weaponInfo->missileTrailFunc = CG_PlasmaTrail;
		weaponInfo->missileSound = trap_S_RegisterSound( "sound/weapons/plasma/lasfly.wav", qfalse );
		MAKERGB( weaponInfo->flashDlightColor, 0.6f, 0.6f, 1.0f );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/plasma/hyprbf1a.wav", qfalse );
		cgs.media.plasmaExplosionShader = trap_R_RegisterShader( "plasmaExplosion" );
		cgs.media.railRingsShader = trap_R_RegisterShader( "railDisc" );
		break;

	case WP_RAILGUN:
		weaponInfo->readySound = trap_S_RegisterSound( "sound/weapons/railgun/rg_hum.wav", qfalse );
		MAKERGB( weaponInfo->flashDlightColor, 1, 0.5f, 0 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/railgun/railgf1a.wav", qfalse );
		cgs.media.railExplosionShader = trap_R_RegisterShader( "railExplosion" );
		cgs.media.railRingsShader = trap_R_RegisterShader( "railDisc" );
		cgs.media.railCoreShader = trap_R_RegisterShader( "railCore" );
		break;

	case WP_BFG:
		weaponInfo->readySound = trap_S_RegisterSound( "sound/weapons/bfg/bfg_hum.wav", qfalse );
		MAKERGB( weaponInfo->flashDlightColor, 1, 0.7f, 1 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/bfg/bfg_fire.wav", qfalse );
		cgs.media.bfgExplosionShader = trap_R_RegisterShader( "bfgExplosion" );
		weaponInfo->missileModel = trap_R_RegisterModel( "models/weaphits/bfg.md3" );
		weaponInfo->missileSound = trap_S_RegisterSound( "sound/weapons/rocket/rockfly.wav", qfalse );
		break;

	 default:
		MAKERGB( weaponInfo->flashDlightColor, 1, 1, 1 );
		weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/rocket/rocklf1a.wav", qfalse );
		break;
	}
