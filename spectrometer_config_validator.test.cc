#include <memory>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "spectrometer_config_validator.h"
#include "spectrometer_structures.h"
#include "spectrometer.h"
#include "type.h"

#include "mock/MockAvaSpecConnection.h"

template <typename TYPE>
void RemoveOutOfBoundValue(std::string type,
        std::vector<struct spec_config_param> config_vector,
        std::vector<struct spec_config_param> expected_vector)
{
    SpectrometerConfigurationValidator<TYPE>
    validator(type);

    std::vector<struct spec_config_param>
    validated_config = validator.validate(config_vector);

    for(typename std::vector<struct spec_config_param>::size_type
        i = 0; i != validated_config.size(); i++)
    {
        EXPECT_EQ(expected_vector[i].name, validated_config[i].name);
        EXPECT_EQ(expected_vector[i].value, validated_config[i].value);
    }
}

class SpectrometerTest : public ::testing::Test
{
protected:
    SpectrometerTest()
    : mockConnection_(std::make_shared<MockAvaSpecConnection>())
    {}

    // Code that runs in every test
    virtual void SetUp()
    {
    }

    // Code that tears down every test goes here
    virtual void TearDown()
    {}

    // Member objects available to all tests
    // Mock a connection to the spectrometer to allow for testing
    std::shared_ptr<MockAvaSpecConnection> mockConnection_;
    // Default parameters for configuration 
    std::vector<struct spec_config_param>
    config_vector_ =
    {
        spec_config_param {
            "uint32",
            "start_pixel",
            "4100"
        },
        spec_config_param {
            "uint32",
            "stop_pixel",
            "15"
        }
    };


};

TEST_F(SpectrometerTest, InitializeConnection)
{
    using ::testing::Return;
    using ::testing::AtLeast;

    Spectrometer s(config_vector_, mockConnection_);
    EXPECT_CALL(*mockConnection_, Init(1))
    .Times(AtLeast(1))
    .WillOnce(Return(0)) // first call returns 0
    .WillOnce(Return(1)); // second call returns 1;

    s.activate();
}

/**

TEST(UINT32Validator, RemoveOutOfBoundValue)
{
    std::vector<struct spec_config_param>
    config_vector =
    {
        spec_config_param {
            "uint32",
            "start_pixel",
            "4100"
        },
        spec_config_param {
            "uint32",
            "stop_pixel",
            "15"
        }
    };

    std::vector<struct spec_config_param>
    expected_vector =
    {
        spec_config_param {
            "INVALID",
            "start_pixel",
            "4100"
        },
        spec_config_param {
            "uint32",
            "stop_pixel",
            "15"
        }
    };

    RemoveOutOfBoundValue<uint32>("uint32",
            config_vector,
            expected_vector);
}

TEST(FLOATValidator, RemoveOutOfBoundValue)
{
    std::vector<struct spec_config_param>
    config_vector =
    {
        spec_config_param {
            "float",
            "integration_time",
            "0.0"
        },
        spec_config_param {
            "float",
            "laser_wavelength",
            "0x32"
        }
    };

    std::vector<struct spec_config_param>
    expected_vector =
    {
        spec_config_param {
            "INVALID",
            "integration_time",
            "0.0"
        },
        spec_config_param {
            "float",
            "laser_wavelength",
            "0x32"
        }
    };

    RemoveOutOfBoundValue<float>("float",
            config_vector,
            expected_vector);
}

TEST(UINT16Validator, RemoveOutOfBoundValue)
{
    std::vector<struct spec_config_param>
    config_vector =
    {
        spec_config_param {
            "uint16",
            "strobe_control",
            "0x40"
        },
        spec_config_param {
            "uint16",
            "smooth_pixel",
            "2050"
        }
    };

    std::vector<struct spec_config_param>
    expected_vector =
    {
        spec_config_param {
            "uint16",
            "strobe_control",
            "0x40"
        },
        spec_config_param {
            "INVALID",
            "smooth_pixel",
            "2050"
        }
    };

    RemoveOutOfBoundValue<uint16>("uint16",
            config_vector,
            expected_vector);
}

TEST(UINT8Validator, RemoveOutOfBoundValue)
{
    std::vector<struct spec_config_param>
    config_vector =
    {
        spec_config_param {
            "uint8",
            "enable",
            "2"
        },
        spec_config_param {
            "uint8",
            "smooth_model",
            "0"
        }
    };

    std::vector<struct spec_config_param>
    expected_vector =
    {
        spec_config_param {
            "INVALID",
            "enable",
            "2"
        },
        spec_config_param {
            "uint8",
            "smooth_model",
            "0"
        }
    };

    RemoveOutOfBoundValue<uint8>("uint8",
            config_vector,
            expected_vector);
}
*/

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/* vim: set ts=4 sw=4 et :*/
