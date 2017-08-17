#ifndef GPSRTKPLUGIN_H
#define GPSRTKPLUGIN_H

#include <rqt_gui_cpp/plugin.h>
#include <ui_gps_rtk_plugin.h>
#include <QWidget>

#include <unistd.h>

#include <ros/ros.h>
#include <piksi_rtk_msgs/ReceiverState.h>
#include <piksi_rtk_msgs/BaselineNed.h>
#include <piksi_rtk_msgs/InfoWifiCorrections.h>
#include <piksi_rtk_msgs/Heartbeat.h>
#include <sensor_msgs/NavSatFix.h>

class GpsRtkPlugin : public rqt_gui_cpp::Plugin {
  Q_OBJECT
public:
  GpsRtkPlugin();
  virtual void initPlugin(qt_gui_cpp::PluginContext& context);
  virtual void shutdownPlugin();
  virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const;
  virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings);

  // Comment in to signal that the plugin has a way to configure it
  //bool hasConfiguration() const;
  //void triggerConfiguration();
private:
  Ui::GpsRtkPlugin ui_;
  QWidget* widget_;

  void readParameters();
  void initLabels();
  void initSubscribers();

  //subscribers
  ros::Subscriber piksiReceiverStateSub_;
  ros::Subscriber piksiBaselineNedSub_;
  ros::Subscriber piksiWifiCorrectionsSub_;
  ros::Subscriber piksiNavsatfixRtkFixSub_;
  ros::Subscriber piksiHeartbeatSub_;

  void piksiReceiverStateCb(const piksi_rtk_msgs::ReceiverState& msg);
  void piksiBaselineNedCb(const piksi_rtk_msgs::BaselineNed& msg);
  void piksiWifiCorrectionsCb(const piksi_rtk_msgs::InfoWifiCorrections& msg);
  void piksiNavsatfixRtkFixCb(const sensor_msgs::NavSatFix& msg);
  void piksiHeartbeatCb(const piksi_rtk_msgs::Heartbeat& msg);

  std::string piksiReceiverStateTopic_;
  std::string piksiBaselineNedTopic_;
  std::string piksiWifiCorrectionsTopic_;
  std::string piksiNavsatfixRtkFixTopic_;
  std::string piksiHeartbeatTopic_;

  double lastHeartbeatStamp_;
  double timeFirstSampleMovingWindow_;
  int wifiCorrectionsAvgHz_;
  int numCorrectionsFirstSampleMovingWindow_;
  std::vector<double> altitudes_;

protected slots:
  //line edits

signals:
  void stateChanged();
};

#endif // GPSRTKPLUGIN_H
