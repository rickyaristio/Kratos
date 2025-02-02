//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license:
//kratos/license.txt
//
//  Main authors:    Pooyan Dadvand
//
//

// System includes
#include <unordered_set>

// External includes

// Project includes
#include "testing/testing.h"
#include "containers/nodal_data.h"
#include "includes/stream_serializer.h"
#include "containers/model.h"

namespace Kratos {
namespace Testing {

		KRATOS_TEST_CASE_IN_SUITE(NodalSolutionStepData, KratosCoreFastSuite)
		{
			Model current_model;

			const int repeat = 10;
			ModelPart& model_part = current_model.CreateModelPart("test");
			model_part.AddNodalSolutionStepVariable(DISTANCE);
			model_part.AddNodalSolutionStepVariable(VELOCITY);

			const std::size_t size = 10;
			for (std::size_t i = 0; i < size; i++)
				model_part.CreateNewNode(i, i, 0, 0);

			for (int i = 0; i < repeat; i++) {
				for (auto i_node = model_part.NodesBegin(); i_node != model_part.NodesEnd(); i_node++) {
					i_node->FastGetSolutionStepValue(DISTANCE) = static_cast<double>(i);
					i_node->FastGetSolutionStepValue(VELOCITY_X) = static_cast<double>(i);
				}
				double distance_sum = 0;
				double velocity_x_sum = 0;
				for (auto i_node = model_part.NodesBegin(); i_node != model_part.NodesEnd(); i_node++) {
					distance_sum += i_node->FastGetSolutionStepValue(DISTANCE);
					velocity_x_sum += i_node->FastGetSolutionStepValue(VELOCITY_X) * 2;
				}
				KRATOS_CHECK_DOUBLE_EQUAL(distance_sum, i * size);
				KRATOS_CHECK_DOUBLE_EQUAL(velocity_x_sum, i * size * 2);
			}
		}

		KRATOS_TEST_CASE_IN_SUITE(FluidNodalSolutionStepData, KratosCoreFastSuite)
		{
			Model current_model;
			
			const int repeat = 10;
			ModelPart& model_part = current_model.CreateModelPart("test");
			model_part.AddNodalSolutionStepVariable(PRESSURE);
			model_part.AddNodalSolutionStepVariable(VELOCITY);
			model_part.AddNodalSolutionStepVariable(FRACT_VEL);
			model_part.AddNodalSolutionStepVariable(MESH_VELOCITY);
			model_part.AddNodalSolutionStepVariable(NODAL_AREA);
			model_part.AddNodalSolutionStepVariable(BODY_FORCE);
			model_part.AddNodalSolutionStepVariable(DENSITY);
			model_part.AddNodalSolutionStepVariable(VISCOSITY);
			model_part.AddNodalSolutionStepVariable(FLAG_VARIABLE);
			model_part.AddNodalSolutionStepVariable(DISPLACEMENT);
			model_part.AddNodalSolutionStepVariable(REACTION);
			model_part.AddNodalSolutionStepVariable(NORMAL);
			std::size_t size = 10;
			for (std::size_t i = 0; i < size; i++)
				model_part.CreateNewNode(i, i, 0, 0);

			for (int i = 0; i < repeat; i++) {
				for (auto i_node = model_part.NodesBegin(); i_node != model_part.NodesEnd(); i_node++) {
					i_node->FastGetSolutionStepValue(PRESSURE) = static_cast<double>(i);
					i_node->FastGetSolutionStepValue(VELOCITY_X) = static_cast<double>(2*i);
				}
				double pressure_sum = 0;
				double velocity_x_sum = 0;
				double velocity_y_sum = 0;
				for (auto i_node = model_part.NodesBegin(); i_node != model_part.NodesEnd(); i_node++) {
					pressure_sum += i_node->FastGetSolutionStepValue(PRESSURE);
					velocity_x_sum += i_node->FastGetSolutionStepValue(VELOCITY_X);
					velocity_y_sum += i_node->FastGetSolutionStepValue(VELOCITY_Y);
				}
				KRATOS_CHECK_DOUBLE_EQUAL(pressure_sum, i * size);
				KRATOS_CHECK_DOUBLE_EQUAL(velocity_x_sum, 2*i * size);
				KRATOS_CHECK_DOUBLE_EQUAL(velocity_y_sum, 0.00);
			}
		}

		KRATOS_TEST_CASE_IN_SUITE(NodalSolutionStepDataSerialization, KratosCoreFastSuite)
		{
			Model current_model;

			ModelPart& model_part = current_model.CreateModelPart("test");
			model_part.AddNodalSolutionStepVariable(DISTANCE);
			model_part.AddNodalSolutionStepVariable(VELOCITY);

            StreamSerializer serializer;

            const std::string tag_string("Node");


			Node::Pointer p_node_to_be_saved = model_part.CreateNewNode(1, 1, 0, 0);
			p_node_to_be_saved->FastGetSolutionStepValue(DISTANCE) = 1.12;
			p_node_to_be_saved->FastGetSolutionStepValue(VELOCITY_X) = 2.32;

			Node::Pointer p_node_to_be_loaded(nullptr);
 
            serializer.save(tag_string, p_node_to_be_saved);
            serializer.load(tag_string, p_node_to_be_loaded);

			KRATOS_CHECK_EQUAL(p_node_to_be_loaded->Id() , 1);
			KRATOS_CHECK_DOUBLE_EQUAL(p_node_to_be_loaded->FastGetSolutionStepValue(DISTANCE), 1.12);
			KRATOS_CHECK_DOUBLE_EQUAL(p_node_to_be_loaded->FastGetSolutionStepValue(VELOCITY_X), 2.32);
		}

        KRATOS_TEST_CASE_IN_SUITE(NodalDataSerialization, KratosCoreFastSuite) {
			Model current_model;

			ModelPart& model_part = current_model.CreateModelPart("test");
			model_part.AddNodalSolutionStepVariable(DISTANCE);
			model_part.AddNodalSolutionStepVariable(VELOCITY);

            NodalData nodal_data_to_be_saved(23, &model_part.GetNodalSolutionStepVariablesList());
            NodalData nodal_data_to_be_loaded(42, &model_part.GetNodalSolutionStepVariablesList());

            StreamSerializer serializer;

            serializer.save("NodalData", nodal_data_to_be_saved);
            serializer.load("NodalData", nodal_data_to_be_loaded);

            KRATOS_CHECK_EQUAL(nodal_data_to_be_saved.Id(), nodal_data_to_be_loaded.Id());
        }

}
} // namespace Kratos.
