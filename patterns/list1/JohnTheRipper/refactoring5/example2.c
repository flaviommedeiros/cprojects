#ifdef ProvideFastSqueeze1344
if ((inLaneCount == 0) && (outLaneCount == 21))
        KeccakF1600_StateXORPermuteExtract_squeeze1344(state, outData, outLaneCount);
    else
#endif
    {
        declareABCDE
        #if (Unrolling != 24)
        unsigned int i;
        #endif
        UINT64 *stateAsLanes = (UINT64*)state;
        UINT64 *inDataAsLanes = (UINT64*)inData;
        UINT64 *outDataAsLanes = (UINT64*)outData;

        copyFromStateAndXOR(A, stateAsLanes, inDataAsLanes, inLaneCount)
        rounds
        copyToStateAndOutput(A, stateAsLanes, outDataAsLanes, outLaneCount)
    }
