namespace test {

class AudioChecksum : public AudioSink {
 public:
  AudioChecksum() : finished_(false) {}

  virtual bool WriteArray(const int16_t* audio, size_t num_samples) OVERRIDE {
    if (finished_)
      return false;

#ifndef WEBRTC_ARCH_LITTLE_ENDIAN
#error "Big-endian gives a different checksum"
#endif
    checksum_.Update(audio, num_samples * sizeof(*audio));
    return true;
  }

  // Finalizes the computations, and returns the checksum.
  std::string Finish() {
    if (!finished_) {
      finished_ = true;
      checksum_.Finish(checksum_result_, rtc::Md5Digest::kSize);
    }
    return rtc::hex_encode(checksum_result_, rtc::Md5Digest::kSize);
  }

 private:
  rtc::Md5Digest checksum_;
  char checksum_result_[rtc::Md5Digest::kSize];
  bool finished_;

  DISALLOW_COPY_AND_ASSIGN(AudioChecksum);
}
