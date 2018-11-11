#include <vector>
#include "service/algo/facial.h"
//#include <opencv/opencv2>

namespace service {
namespace algo {

struct Rect {
  int x;
  int y;
  int width;
  int height;
};

struct Point {
  int x;
  int y;
};

grpc::Status Facial::FacialDetect(grpc::ClientContext* context,
    const iface::param::FacialDetectParams& request,
    iface::param::FacialDetectResponse* response) {
  std::string path;
  // TODO fetch request.url
  std::string res;
  // TODO invoke algo detect with path
  std::vector<Rect> regions;
  std::vector<std::vector<Point>> landmarks;
  
  for (auto &reg : regions) {
    auto r = response->add_regions();
    r->set_x(reg.x);
    r->set_y(reg.y);
    r->set_width(reg.width);
    r->set_height(reg.height);
  }

  for (auto &r : landmarks) {
    auto l = response->add_landmarks();
    for (auto &lm : r) {
      auto p = l->add_pts();
      p->set_x(lm.x);
      p->set_y(lm.y);
    }
  }

  return grpc::Status::OK;
}

grpc::Status Facial::ExtractFeature(grpc::ClientContext* context, 
    const iface::param::ExtractFeatureParams& request, 
    iface::param::ExtractFeatureResponse* response) {
  std::string path;
  // TODO fetch request.url

  std::string res;
  // TODO invoke algo extract with path
  response->set_feat(res);
  return grpc::Status::OK;
}

grpc::Status Facial::Similarity(grpc::ClientContext* context,
    const iface::param::SimilarityParams& request,
    iface::param::SimilarityResponse* response) {
  float score = 0.0;
  // TODO invoke algo similarity
  //score = similarity(request.feat1, request.feat2);
  response->set_score(score);
  return grpc::Status::OK;
}

}} // namespace service::algo
