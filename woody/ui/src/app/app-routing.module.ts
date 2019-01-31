import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { ClickstreamComponent } from './clickstream/clickstream.component';
import { UserProfileComponent } from './user-profile/user-profile.component';
import { IndexComponent } from './index/index.component';

const routes: Routes = [
  { path: 'clickstream', component: ClickstreamComponent },
  { path: 'profile', component: UserProfileComponent },
  { path: '', component: IndexComponent },
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
