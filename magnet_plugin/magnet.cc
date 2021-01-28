#include <functional>
#include <gazebo/physics/physics.hh>
#include <gazebo/physics/ModelState.hh>
#include <gazebo/physics/LinkState.hh>
#include <gazebo/physics/CollisionState.hh>
#include <gazebo/common/common.hh>
#include <gazebo/math/Vector3.hh>
#include <sdformat-4.0/sdf/Element.hh>
#include <gazebo/physics/Link.hh>
#include <gazebo/transport/transport.hh>

#include <string>

//<plugin name='magnet' filename='libmagnet.so'/>

namespace gazebo
{
    class magnet : public ModelPlugin
    {
    public: void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf)
        {

            this->World = _model->GetWorld();

            this->model=_model;


            std::string self_name=_model->GetName();
            int n=self_name.find("_");
            std::string num=self_name.substr(n+1, self_name.length());

            this->ID=std::stoi(num);

            // Listen to the update event. This event is broadcast every simulation iteration.
            this->updateConnection = event::Events::ConnectWorldUpdateBegin(std::bind(&magnet::OnUpdate, this));

        }
        // Called by the world update start event
    public: void OnUpdate()
        {

            const int module_num=2;
            int connection[][module_num]={{0,0},{1,0}};

            this->link_0=this->model->GetChildLink("link_0");
//            physics::Joint_V ja=this->link_0->GetChildJoints();
//            physics::JointPtr j0=this->model->GetJoint("link_0_JOINT");
//            j0->SetParent(this->link_0);
//            this->link=this->model->GetChildLink("link_1");

            for (int i = 0; i < module_num; ++i){
                //ID is attached to i
                if (connection[this->ID][i]==1){

                    physics::ModelPtr support = this->World->GetModel("sphere_"+std::to_string(i));
                    physics::LinkPtr support_link=support->GetLink("link");
                    const math::Pose& support_pose=support_link->GetWorldPose();

                    const math::Pose& magnet_pose=this->link_0->GetWorldPose();

                    math::Vector3 dis=math::Vector3(support_pose.pos-magnet_pose.pos);
                    double dis_l=dis.GetLength();
                    double radius=0.1;
                    if (dis_l<10*radius){
                        math::Vector3 dis_n=dis.Normalize();
                        //this->link_0->AddParentJoint()//this->link_0
                        support_link->AddForce(-10*dis_n);
                        this->link_0->AddForce(10*dis_n);

                    }
                }
            }
        }


        // Pointer to the model
    private: physics::ModelPtr model;
    private: int ID;
    private: physics::LinkPtr link_0;

    private: physics::WorldPtr World;

        // Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;
    };

    // Register this plugin with the simulator
    GZ_REGISTER_MODEL_PLUGIN(magnet)
}
