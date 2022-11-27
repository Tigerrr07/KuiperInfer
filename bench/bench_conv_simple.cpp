//
// Created by fss on 22-11-22.
//
#include <benchmark/benchmark.h>
#include "parser/runtime_ir.hpp"
#include "data/load_data.hpp"
static void BM_ConvSimple(benchmark::State &state) {
  using namespace kuiper_infer;
  RuntimeGraph graph("tmp/im2cols/convlarge.pnnx.param",
                     "tmp/im2cols/convlarge.pnnx.bin");
  graph.Build("pnnx_input_0", "pnnx_output_0");

  std::vector<std::shared_ptr<Tensor<float>>> inputs;
  std::shared_ptr<Tensor<float>> input_tensor = std::make_shared<Tensor<float>>(3, 512, 512);
  input_tensor->at(0) = CSVDataLoader::LoadData("./tmp/im2cols/1_large.csv");
  input_tensor->at(1) = CSVDataLoader::LoadData("./tmp/im2cols/2_large.csv");
  input_tensor->at(2) = CSVDataLoader::LoadData("./tmp/im2cols/3_large.csv");
  inputs.push_back(input_tensor);

  for (auto _ : state) {
    const auto &output = graph.Forward(inputs, false);
  }
}

static void BM_ConvIdentity(benchmark::State &state) {
  using namespace kuiper_infer;
  RuntimeGraph graph("tmp/resnet_identity/resnet_identity_graph_big.pnnx.param",
                     "tmp/resnet_identity/resnet_identity_graph_big.pnnx.bin");

  graph.Build("pnnx_input_0", "pnnx_output_0");

  std::shared_ptr<Tensor<float>> input = std::make_shared<Tensor<float>>(3, 512, 512);
  input->Ones();

  std::vector<std::shared_ptr<Tensor<float>>> inputs;
  inputs.push_back(input);

  for (auto _ : state) {
    const auto &output = graph.Forward(inputs, false);
  }
}

static void BM_ConvIdentity2(benchmark::State &state) {
  using namespace kuiper_infer;
  RuntimeGraph graph("tmp/resnet_identity/resnet_identity_graph_max.pnnx.param",
                     "tmp/resnet_identity/resnet_identity_graph_max.pnnx.bin");

  graph.Build("pnnx_input_0", "pnnx_output_0");

  std::shared_ptr<Tensor<float>> input = std::make_shared<Tensor<float>>(3, 512, 512);
  input->Ones();

  std::vector<std::shared_ptr<Tensor<float>>> inputs;
  inputs.push_back(input);

  for (auto _ : state) {
    const auto &output = graph.Forward(inputs, false);
  }
}

static void BM_ConvIdentity3(benchmark::State &state) {
  using namespace kuiper_infer;
  RuntimeGraph graph
      ("tmp/resnet_identity/resnet_identity_graph_max2.pnnx.param",
       "tmp/resnet_identity/resnet_identity_graph_max2.pnnx.bin");

  graph.Build("pnnx_input_0", "pnnx_output_0");

  std::shared_ptr<Tensor<float>> input = std::make_shared<Tensor<float>>(3, 512, 512);
  input->Ones();

  std::vector<std::shared_ptr<Tensor<float>>> inputs;
  inputs.push_back(input);

  for (auto _ : state) {
    const auto &output = graph.Forward(inputs, false);
  }
}

BENCHMARK(BM_ConvSimple);
BENCHMARK(BM_ConvIdentity);
BENCHMARK(BM_ConvIdentity2);
BENCHMARK(BM_ConvIdentity3);

BENCHMARK_MAIN();