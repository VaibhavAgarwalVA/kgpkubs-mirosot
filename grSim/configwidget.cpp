/*
grSim - RoboCup Small Size Soccer Robots Simulator
Copyright (C) 2011, Parsian Robotic Center (eew.aut.ac.ir/~parsian/grsim)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "configwidget.h"

#define ADD_ENUM(type,name,Defaultvalue,namestring) \
v_##name = new Var##type(namestring,Defaultvalue);
#define END_ENUM(parents, name) \
parents->addChild(v_##name);
#define ADD_TO_ENUM(name,str) \
v_##name->addItem(str);


#define ADD_VALUE(parent,type,name,defaultvalue,namestring) \
    v_##name = new Var##type(namestring,defaultvalue); \
    parent->addChild(v_##name);

#include<QDir>


ConfigWidget::ConfigWidget()
{  
  tmodel=new VarTreeModel();
  this->setModel(tmodel);  
  geo_vars = new VarList("Geometry");
  world.push_back(geo_vars);  
  robot_settings = new QSettings;
    VarList * field_vars = new VarList("Field");
    geo_vars->addChild(field_vars);
        ADD_VALUE(field_vars,Double,Field_Length,6.05,"Length")
        ADD_VALUE(field_vars,Double,Field_Width,4.05,"Width")
        ADD_VALUE(field_vars,Double,Field_Rad,0.5,"Radius")
        ADD_VALUE(field_vars,Double,Field_Penalty_Rad,0.50,"Penalty radius")
        ADD_VALUE(field_vars,Double,Field_Penalty_Line,0.350,"Penalty line length")
        ADD_VALUE(field_vars,Double,Field_Penalty_Point,0.450,"Penalty point")
        ADD_VALUE(field_vars,Double,Field_Margin,1.0,"Margin")
        ADD_VALUE(field_vars,Double,Field_Referee_Margin,0.7,"Referee margin")
        ADD_VALUE(field_vars,Double,Wall_Thickness,0.100,"Wall thickness")
        ADD_VALUE(field_vars,Double,Goal_Thickness,0.020,"Goal thickness")
        ADD_VALUE(field_vars,Double,Goal_Depth,0.20,"Goal depth")
        ADD_VALUE(field_vars,Double,Goal_Width,0.70,"Goal width")
        ADD_VALUE(field_vars,Double,Goal_Height,0.40,"Goal height")
    ADD_ENUM(StringEnum,YellowTeam,"Parsian","Yellow Team");
    END_ENUM(geo_vars,YellowTeam)
    ADD_ENUM(StringEnum,BlueTeam,"Parsian","Blue Team");
    END_ENUM(geo_vars,BlueTeam)

    VarList * ballg_vars = new VarList("Ball");
    geo_vars->addChild(ballg_vars);
        ADD_VALUE(ballg_vars,Double,BallRadius,0.0215,"Radius")
  VarList * phys_vars = new VarList("Physics");
  world.push_back(phys_vars);
    VarList * worldp_vars = new VarList("World");    
    phys_vars->addChild(worldp_vars);  
        ADD_VALUE(worldp_vars,Double,DesiredFPS,65,"Desired FPS")
        ADD_VALUE(worldp_vars,Bool,SyncWithGL,false,"Synchronize ODE with OpenGL")
        ADD_VALUE(worldp_vars,Double,DeltaTime,0.015,"ODE time step")
        ADD_VALUE(worldp_vars,Double,Gravity,9.8,"Gravity")
  VarList * ballp_vars = new VarList("Ball");
    phys_vars->addChild(ballp_vars);
        ADD_VALUE(ballp_vars,Double,BallMass,0.043,"Ball mass");
        ADD_VALUE(ballp_vars,Double,BallFriction,0.05,"Ball-ground friction")
        ADD_VALUE(ballp_vars,Double,BallSlip,1,"Ball-ground slip")
        ADD_VALUE(ballp_vars,Double,BallBounce,0.05,"Ball-ground bounce factor")
        ADD_VALUE(ballp_vars,Double,BallBounceVel,0.01,"Ball-ground bounce min velocity")
        ADD_VALUE(ballp_vars,Double,BallLinearDamp,0.04,"Ball linear damping")
        ADD_VALUE(ballp_vars,Double,BallAngularDamp,0.004,"Ball angular damping")
  VarList * comm_vars = new VarList("Communication");
  world.push_back(comm_vars);
    ADD_VALUE(comm_vars,String,VisionMulticastAddr,"224.5.23.2","Vision multicast address")  //SSL Vision: "224.5.23.2"
    ADD_VALUE(comm_vars,Int,VisionMulticastPort,10002,"Vision multicast port")
    ADD_VALUE(comm_vars,Int,CommandListenPort,20012,"Command listen port")
    ADD_VALUE(comm_vars,Int,BlueStatusSendPort,30011,"Blue Team status send port")
    ADD_VALUE(comm_vars,Int,YellowStatusSendPort,30012,"Yellow Team status send port")
    ADD_VALUE(comm_vars,Int,sendDelay,0,"Sending delay (milliseconds)")
    VarList * gauss_vars = new VarList("Gaussian noise");
        comm_vars->addChild(gauss_vars);
        ADD_VALUE(gauss_vars,Bool,noise,false,"Noise")
        ADD_VALUE(gauss_vars,Double,noiseDeviation_x,3,"Deviation for x values")
        ADD_VALUE(gauss_vars,Double,noiseDeviation_y,3,"Deviation for y values")
        ADD_VALUE(gauss_vars,Double,noiseDeviation_angle,2,"Deviation for angle values")
    VarList * vanishing_vars = new VarList("Vanishing probability");
        comm_vars->addChild(vanishing_vars);
        ADD_VALUE(gauss_vars,Bool,vanishing,false,"Vanishing")
        ADD_VALUE(vanishing_vars,Double,blue_team_vanishing,0,"Blue team")
        ADD_VALUE(vanishing_vars,Double,yellow_team_vanishing,0,"Yellow team")
        ADD_VALUE(vanishing_vars,Double,ball_vanishing,0,"Ball")
    world=VarXML::read(world,(qApp->applicationDirPath() + QString("/settings.xml")).toStdString());


    QDir dir;
    std::string blueteam = v_BlueTeam->getString();
    geo_vars->removeChild(v_BlueTeam);

    std::string yellowteam = v_YellowTeam->getString();
    geo_vars->removeChild(v_YellowTeam);

    ADD_ENUM(StringEnum,BlueTeam,blueteam.c_str(),"Blue Team");
    ADD_ENUM(StringEnum,YellowTeam,yellowteam.c_str(),"Yellow Team");
    dir.setCurrent(qApp->applicationDirPath()+"/../config/");
    dir.setNameFilters(QStringList() << "*.ini");
    dir.setSorting(QDir::Size | QDir::Reversed);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
    QFileInfo fileInfo = list.at(i);
    QStringList s = fileInfo.fileName().split(".");
    QString str;
    if (s.count() > 0) str = s[0];
        ADD_TO_ENUM(BlueTeam,str.toStdString())
        ADD_TO_ENUM(YellowTeam,str.toStdString())
    }
    END_ENUM(geo_vars,BlueTeam)
    END_ENUM(geo_vars,YellowTeam)

  v_BlueTeam->setString(blueteam);
  v_YellowTeam->setString(yellowteam);

  tmodel->setRootItems(world);

  this->expandAndFocus(geo_vars);
  this->expandAndFocus(phys_vars);
  this->expandAndFocus(comm_vars);

  this->fitColumns();

  resize(320,400);
  connect(v_BlueTeam, SIGNAL(wasEdited(VarType*)), this, SLOT(loadRobotsSettings()));
  connect(v_YellowTeam, SIGNAL(wasEdited(VarType*)), this, SLOT(loadRobotsSettings()));
  loadRobotsSettings();
}

ConfigWidget::~ConfigWidget() {  
   VarXML::write(world,(qApp->applicationDirPath() + QString("/settings.xml")).toStdString());
}


ConfigDockWidget::ConfigDockWidget(QWidget* _parent,ConfigWidget* _conf){
    parent=_parent;conf=_conf;
    setWidget(conf);
    conf->move(0,20);
}  
void ConfigDockWidget::closeEvent(QCloseEvent* event)
{
    emit closeSignal(false);
}


void ConfigWidget::loadRobotsSettings()
{
    loadRobotSettings(YellowTeam().c_str());
    yellowSettings = robotSettings;
    loadRobotSettings(BlueTeam().c_str());
    blueSettings = robotSettings;
}

void ConfigWidget::loadRobotSettings(QString team)
{
    QString ss = qApp->applicationDirPath()+QString("/../config/")+QString("%1.ini").arg(team);
    robot_settings = new QSettings(ss, QSettings::IniFormat);
    robotSettings.RobotCenterFromKicker = robot_settings->value("Geometery/CenterFromKicker", 0.073).toDouble();
    robotSettings.RobotRadius = robot_settings->value("Geometery/Radius", 0.09).toDouble();
    robotSettings.RobotHeight = robot_settings->value("Geometery/Height", 0.13).toDouble();
    robotSettings.BottomHeight = robot_settings->value("Geometery/RobotBottomZValue", 0.02).toDouble();
    robotSettings.KickerZ = robot_settings->value("Geometery/KickerZValue", 0.005).toDouble();
    robotSettings.KickerThickness = robot_settings->value("Geometery/KickerThickness", 0.005).toDouble();
    robotSettings.KickerWidth = robot_settings->value("Geometery/KickerWidth", 0.08).toDouble();
    robotSettings.KickerHeight = robot_settings->value("Geometery/KickerHeight", 0.04).toDouble();
    robotSettings.WheelRadius = robot_settings->value("Geometery/WheelRadius", 0.0325).toDouble();
    robotSettings.WheelThickness = robot_settings->value("Geometery/WheelThickness", 0.005).toDouble();
    robotSettings.Wheel1Angle = robot_settings->value("Geometery/Wheel1Angle", 60).toDouble();
    robotSettings.Wheel2Angle = robot_settings->value("Geometery/Wheel2Angle", 135).toDouble();
    robotSettings.Wheel3Angle = robot_settings->value("Geometery/Wheel3Angle", 225).toDouble();
    robotSettings.Wheel4Angle = robot_settings->value("Geometery/Wheel4Angle", 300).toDouble();

    robotSettings.BodyMass  = robot_settings->value("Physics/BodyMass", 2).toDouble();
    robotSettings.WheelMass = robot_settings->value("Physics/WheelMass", 0.2).toDouble();
    robotSettings.KickerMass= robot_settings->value("Physics/KickerMass",0.02).toDouble();
    robotSettings.KickerDampFactor = robot_settings->value("Physics/KickerDampFactor", 0.2f).toDouble();
    robotSettings.RollerTorqueFactor = robot_settings->value("Physics/RollerTorqueFactor", 0.06f).toDouble();
    robotSettings.RollerPerpendicularTorqueFactor = robot_settings->value("Physics/RollerPerpendicularTorqueFactor", 0.005f).toDouble();
    robotSettings.Kicker_Friction = robot_settings->value("Physics/KickerFriction", 0.8f).toDouble();
    robotSettings.WheelTangentFriction = robot_settings->value("Physics/WheelTangentFriction", 0.8f).toDouble();
    robotSettings.WheelPerpendicularFriction = robot_settings->value("Physics/WheelPerpendicularFriction", 0.05f).toDouble();
    robotSettings.Wheel_Motor_FMax = robot_settings->value("Physics/WheelMotorMaximumApplyingTorque", 0.2f).toDouble();
}
