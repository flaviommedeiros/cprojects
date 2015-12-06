if (!(
            indicatorFlashNow ||
            rotationUpdateNow ||
            warningFlashNow
#ifdef USE_LED_ANIMATION
            || animationUpdateNow
#endif
    )) {
        return;
    }
