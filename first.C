void first()
{
   base::ProcMgr::instance()->SetRawAnalysis(true);
   base::ProcMgr::instance()->SetTriggeredAnalysis(true);

   // all new instances get this value
   base::ProcMgr::instance()->SetHistFilling(4);

   // this limits used for liner calibrations when nothing else is available
   hadaq::TdcMessage::SetFineLimits(31, 491);

   // default channel numbers and edges mask
   hadaq::TrbProcessor::SetDefaults(33, 2);

   // [min..max] range for TDC ids
  // hadaq::TrbProcessor::SetTDCRange(0x900, 0x9FF);

   // [min..max] range for HUB ids
  // hadaq::TrbProcessor::SetHUBRange(0x8100, 0x81FF);

   // when first argument true - TRB/TDC will be created on-the-fly
   // second parameter is function name, called after elements are created
   hadaq::HldProcessor* hld = new hadaq::HldProcessor(true, "after_create");

   // first parameter if filename  prefix for calibration files
   //     and calibration mode (empty string - no file I/O)
   // second parameter is hits count for autocalibration
   //     0 - only load calibration
   //    -1 - accumulate data and store calibrations only at the end
   //    >0 - automatic calibration after N hits in each active channel
   // third parameter is trigger type used for calibration
   //   0xD - special trigger with internal pulser, used also for TOT calibration
   //0xFFFF - all kind of trigger types will be used for calibration, no TOT calibration
   
  
       hld->ConfigureCalibration("calibration_", -1, (1 << 0xD));
   //  hld->ConfigureCalibration("calibration_", 0, 0);

   // only accept trigger type 0x1 when storing file
   // new hadaq::HldFilter(0x1);

   // create ROOT file store
   base::ProcMgr::instance()->CreateStore("td.root");

   // 0 - disable store
   // 1 - std::vector<hadaq::TdcMessageExt> - includes original TDC message
   // 2 - std::vector<hadaq::MessageFloat>  - compact form, without channel 0, stamp as float (relative to ch0)
   // 3 - std::vector<hadaq::MessageDouble> - compact form, with channel 0, absolute time stamp as double
   base::ProcMgr::instance()->SetStoreKind(1);
}
