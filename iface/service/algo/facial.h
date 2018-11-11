#pragma once
#include "service/proto/facial.grpc.pb.h"

namespace service {
namespace algo {

class Facial final : public iface::algo::Facial::Service {

public:
  Facial() = default;
  ~Facial() = default;

  grpc::Status FacialDetect(grpc::ClientContext* context,
      const iface::param::FacialDetectParams& request,
      iface::param::FacialDetectResponse* response);

  grpc::Status ExtractFeature(grpc::ClientContext* context, 
      const iface::param::ExtractFeatureParams& request, 
      iface::param::ExtractFeatureResponse* response);

  grpc::Status Similarity(grpc::ClientContext* context,
      const iface::param::SimilarityParams& request,
      iface::param::SimilarityResponse* response);
};

}} // namespace service::algo
