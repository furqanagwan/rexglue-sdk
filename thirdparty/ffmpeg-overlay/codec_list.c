static const AVCodec* const codec_list[] = {
#if CONFIG_MP3FLOAT_DECODER
    &ff_mp3float_decoder,
#endif
#if CONFIG_MP3_DECODER
    &ff_mp3_decoder,
#endif
#if CONFIG_WMAPRO_DECODER
    &ff_wmapro_decoder,
#endif
#if CONFIG_WMAV2_DECODER
    &ff_wmav2_decoder,
#endif
#if CONFIG_XMAFRAMES_DECODER
    &ff_xmaframes_decoder,
#endif
    /* Whole XMA files (RIFF, 2048-byte packets), for host-side decoding of
       console interface sounds. wmaprodec.c defines these unconditionally. */
    &ff_xma1_decoder,
    &ff_xma2_decoder,
    NULL};
